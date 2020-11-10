/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:07:22 by hjung             #+#    #+#             */
/*   Updated: 2020/11/10 21:25:33 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)game->cub_info->scr_width - 1;
	ray->raydir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->raydir_y = game->player->dir_y + game->player->plane_y * ray->camera_x;
	ray->map_x = (int)game->player->posx;
	ray->map_y = (int)game->player->posy;
	ray->d_dist_x = fabs(1 / ray->raydir_x);
	ray->d_dist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

static void	calc_side_dist(t_game *game, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->s_dist_x = (game->player->posx - ray->map_x) * ray->d_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->s_dist_x = (ray->map_x + 1 - game->player->posx) * ray->d_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->s_dist_y = (game->player->posy - ray->map_y) * ray->d_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->s_dist_y = (ray->map_y + 1 - game->player->posy) * ray->d_dist_y;
	}
}

static void	calc_line_height(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->s_dist_x < ray->s_dist_y)
		{
			ray->s_dist_x += ray->d_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->s_dist_y += ray->d_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->cub_info->map[ray->map_y][ray->map_x] > '0')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player->posx + \
								(1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player->posy + \
								(1 - ray->step_y) / 2) / ray->raydir_y;
	ray->line_height = (int)(game->cub_info->scr_height / ray->perp_wall_dist);
}

void		calc(t_game *game, t_ray *ray)
{
	int		x;

	x = 0;
	coloring_floor_ceiling(game);
	while (x < game->cub_info->scr_width)
	{
		init_ray(game, ray, x);
		calc_side_dist(game, ray);
		calc_line_height(game, ray);
		ray->draw_start = -ray->line_height / 2
							+ game->cub_info->scr_height / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + game->cub_info->scr_height / 2;
		if (ray->draw_end >= game->cub_info->scr_height)
			ray->draw_end = game->cub_info->scr_height - 1;
		adjust_texture(game, ray, x);
		ray->z_buffer[x] = ray->perp_wall_dist;
		x++;
	}

	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < game->num_sprite; i++)
	{
		game->sprites[i].distance = (pow((game->player->posx - game->sprites[i].x), 2) + pow((game->player->posy - game->sprites[i].y), 2));
	}
	sort_sprites(game, game->num_sprite);
	
	//after sorting the sprites, do the projection and draw them
	t_draw_sprite d_sprite;

	for(int i = 0; i < game->num_sprite; i++)
	{
		//translate sprite position to relative to camera
		d_sprite.sprite_x = game->sprites[i].x - game->player->posx;
		d_sprite.sprite_y = game->sprites[i].y - game->player->posy;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		//required for correct matrix multiplication
		d_sprite.inv_det = 1.0 / (game->player->plane_x * game->player->dir_y - game->player->dir_x * game->player->plane_y); 

		d_sprite.transform_x = d_sprite.inv_det * (game->player->dir_y * d_sprite.sprite_x - game->player->dir_x * d_sprite.sprite_y);
		d_sprite.transform_y = d_sprite.inv_det * (-game->player->plane_y * d_sprite.sprite_x + game->player->plane_x * d_sprite.sprite_y); 
		//this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		d_sprite.sprite_screen_x = (int)((game->cub_info->scr_width / 2) * (1 + d_sprite.transform_x / d_sprite.transform_y));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		d_sprite.v_move_screen = (int)(vMove / d_sprite.transform_y);

		//calculate height of the sprite on screen
		d_sprite.sprite_height = (int)fabs((game->cub_info->scr_height / d_sprite.transform_y) / vDiv); 
		//calculate lowest and highest pixel to fill in current stripe
		d_sprite.draw_start_y = -d_sprite.sprite_height / 2 + game->cub_info->scr_height / 2 + d_sprite.v_move_screen;
		if(d_sprite.draw_start_y < 0) d_sprite.draw_start_y = 0;
		d_sprite.draw_end_y = d_sprite.sprite_height / 2 + game->cub_info->scr_height / 2 + d_sprite.v_move_screen;
		if(d_sprite.draw_end_y >= game->cub_info->scr_height) d_sprite.draw_end_y = game->cub_info->scr_height - 1;

		//calculate width of the sprite
		d_sprite.sprite_width = (int)fabs((game->cub_info->scr_height / d_sprite.transform_y) / uDiv);
		d_sprite.draw_start_x = -d_sprite.sprite_width / 2 + d_sprite.sprite_screen_x;
		if(d_sprite.draw_start_x < 0) d_sprite.draw_start_x = 0;
		d_sprite.draw_end_x = d_sprite.sprite_width / 2 + d_sprite.sprite_screen_x;
		if(d_sprite.draw_end_x >= game->cub_info->scr_width) d_sprite.draw_end_x = game->cub_info->scr_width - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = d_sprite.draw_start_x; stripe < d_sprite.draw_end_x; stripe++)
		{
			int texX = (int)((256 * (stripe - (-d_sprite.sprite_width / 2 + d_sprite.sprite_screen_x)) * game->cub_info->textures[4]->img_width / d_sprite.sprite_width) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(d_sprite.transform_y > 0 && stripe > 0 && stripe < game->cub_info->scr_width && d_sprite.transform_y < ray->z_buffer[stripe])
			for(int y = d_sprite.draw_start_y; y < d_sprite.draw_end_y; y++) //for every pixel of the current stripe
			{
				int d = (y-d_sprite.v_move_screen) * 256 - game->cub_info->scr_height * 128 + d_sprite.sprite_height * 128; //256 and 128 factors to avoid floats
				int texY = ((d * game->cub_info->textures[4]->img_height) / d_sprite.sprite_height) / 256;
				int color = game->cub_info->textures[4]->data[game->cub_info->textures[4]->img_width * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) game->img->data[y * game->cub_info->scr_width + stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
	
}

int			game_loop(t_game *game)
{
	t_ray	ray;

	if (!(ray.z_buffer = malloc(sizeof(double) * game->cub_info->scr_width)))
		return (0);
	calc(game, &ray);
	if (game->save == 1)
	{
		game->save = 0;
		capture_bmp(game);
		leave(0, game, "");
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
							game->img->img_ptr, 0, 0);
	return (1);
}
