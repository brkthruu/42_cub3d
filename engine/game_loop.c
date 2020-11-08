/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:07:22 by hjung             #+#    #+#             */
/*   Updated: 2020/11/08 15:52:12 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)game->cub_info->scr_width - 1;
	ray->raydir_x = game->player->dir_x + game->player->plane_x * ray->camera_x;
	ray->raydir_y = game->player->dir_x + game->player->plane_y * ray->camera_x;

	ray->map_x = (int)game->player->posx;
	ray->map_y = (int)game->player->posy;

	ray->d_dist_x = fabs(1 / ray->raydir_x);
	ray->d_dist_y = fabs(1 / ray->raydir_y);

	ray->hit = 0;
}

void	calc_side_dist(t_game *game, t_ray *ray)
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

void	calc_line_height(t_game *game, t_ray *ray)
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
		{
			ray->hit = 1;
		}
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player->posx + \
								(1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player->posy + \
								(1 - ray->step_y) / 2) / ray->raydir_y;
	ray->line_height = (int)(4 * game->cub_info->scr_height / ray->perp_wall_dist);
}

void	verLine(t_game *game, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		y++;
	}
}

void		calc(t_game *game, t_ray *ray)
{
	int	x;

	x = 0;
	
	int height;
	int width;
	height = game->cub_info->scr_height;
	width = game->cub_info->scr_width;

	//FLOOR CASTING
	for(int y = 0; y < height; y++)
	{
		// // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// float rayDirX0 = game->player->dir_x - game->player->plane_x;
		// float rayDirY0 = game->player->dir_y - game->player->plane_y;
		// float rayDirX1 = game->player->dir_x + game->player->plane_x;
		// float rayDirY1 = game->player->dir_y + game->player->plane_y;

		// // Current y position compared to the center of the screen (the horizon)
		// int p = y - height / 2;

		// // Vertical position of the camera.
		// float posZ = 0.5 * height;

		// // Horizontal distance from the camera to the floor for the current row.
		// // 0.5 is the z position exactly in the middle between floor and ceiling.
		// float rowDistance = posZ / p;

		// // calculate the real world step vector we have to add for each x (parallel to camera plane)
		// // adding step by step avoids multiplications with a weight in the inner loop
		// float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		// float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;

		// // real world coordinates of the leftmost column. This will be updated as we step to the right.
		// float floorX = game->player->posx + rowDistance * rayDirX0;
		// float floorY = game->player->posy + rowDistance * rayDirY0;

		for(int x = 0; x < width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			// int cellX = (int)(floorX);
			// int cellY = (int)(floorY);

			// floorX += floorStepX;
			// floorY += floorStepY;

			int color;

			// floor
			color = game->cub_info->color_floor;
			color = (color >> 1) & 8355711; // make a bit darker

			game->img->data[y * game->cub_info->scr_width + x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = game->cub_info->color_ceil;
			color = (color >> 1) & 8355711; // make a bit darker

			game->img->data[(height - y - 1) * width + x] = color;
		}
	}
	
	while (x < game->cub_info->scr_width)
	{
		init_ray(game, ray, x);
		calc_side_dist(game, ray);
		calc_line_height(game, ray);

		//calculate lowest and highest pixel to fill in current stripe
		ray->draw_start = -ray->line_height / 2 + game->cub_info->scr_height / 2;
		if(ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + game->cub_info->scr_height / 2;
		if(ray->draw_end >= game->cub_info->scr_height)
			ray->draw_end = game->cub_info->scr_height - 1;

		// int	color;
		// if (game->cub_info->map[ray->map_y][ray->map_x] == '1')
		// 	color = 0xFF0000;
		// else if (game->cub_info->map[ray->map_y][ray->map_x] == '2')
		// 	color = 0x00FF00;
		// else if (game->cub_info->map[ray->map_y][ray->map_x] == '3')
		// 	color = 0x0000FF;
		// else if (game->cub_info->map[ray->map_y][ray->map_x] == '4')
		// 	color = 0xFFFFFF;
		// else
		//  	color = 0xFFFF00;
		
		// if (ray->side == 1)
		// 	color = color / 2;

		// verLine(game, x, ray->draw_start, ray->draw_end, color);
		
		adjust_texture(game, ray, x);
		x++;
	}
}

int		game_loop(t_game *game)
{
	t_ray	ray;

	calc(game, &ray);
	draw(game);
	return (0);
}