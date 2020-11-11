/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:42:44 by hjung             #+#    #+#             */
/*   Updated: 2020/11/11 18:06:50 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	transform_sprite(t_game *game, t_draw_sprite *d_sp, int i)
{
	d_sp->sprite_x = game->sprites[i].x - game->player->posx;
	d_sp->sprite_y = game->sprites[i].y - game->player->posy;
	d_sp->inv_det = 1.0 / (game->player->plane_x * game->player->dir_y
							- game->player->dir_x * game->player->plane_y);
	d_sp->transform_x = d_sp->inv_det * (game->player->dir_y
			* d_sp->sprite_x - game->player->dir_x * d_sp->sprite_y);
	d_sp->transform_y = d_sp->inv_det * (-game->player->plane_y
			* d_sp->sprite_x + game->player->plane_x * d_sp->sprite_y);
	d_sp->sprite_screen_x = (int)((game->cub_info->scr_width / 2)
					* (1 + d_sp->transform_x / d_sp->transform_y));
	d_sp->v_move_screen = (int)(d_sp->v_move / d_sp->transform_y);
}

static void	calculate_sprite(t_game *game, t_draw_sprite *d_sp)
{
	d_sp->sprite_height = (int)fabs((game->cub_info->scr_height
									/ d_sp->transform_y) / d_sp->v_div);
	d_sp->draw_start_y = -d_sp->sprite_height / 2
					+ game->cub_info->scr_height / 2 + d_sp->v_move_screen;
	if (d_sp->draw_start_y < 0)
		d_sp->draw_start_y = 0;
	d_sp->draw_end_y = d_sp->sprite_height / 2
					+ game->cub_info->scr_height / 2 + d_sp->v_move_screen;
	if (d_sp->draw_end_y >= game->cub_info->scr_height)
		d_sp->draw_end_y = game->cub_info->scr_height - 1;
	d_sp->sprite_width = (int)fabs((game->cub_info->scr_height
									/ d_sp->transform_y) / d_sp->u_div);
	d_sp->draw_start_x = -d_sp->sprite_width / 2 + d_sp->sprite_screen_x;
	if (d_sp->draw_start_x < 0)
		d_sp->draw_start_x = 0;
	d_sp->draw_end_x = d_sp->sprite_width / 2 + d_sp->sprite_screen_x;
	if (d_sp->draw_end_x >= game->cub_info->scr_width)
		d_sp->draw_end_x = game->cub_info->scr_width - 1;
}

static void	draw_sprite_y(t_game *game, t_draw_sprite *d_sp)
{
	d_sp->y = d_sp->draw_start_y;
	while (d_sp->y < d_sp->draw_end_y)
	{
		d_sp->d = (d_sp->y - d_sp->v_move_screen) * 256 - game->\
			cub_info->scr_height * 128 + d_sp->sprite_height * 128;
		d_sp->tex_y = ((d_sp->d * game->cub_info->textures[4]->\
						img_height) / d_sp->sprite_height) / 256;
		d_sp->color = game->cub_info->textures[4]->data[game->cub_info\
					->textures[4]->img_width * d_sp->tex_y + d_sp->tex_x];
		if ((d_sp->color & 0x00FFFFFF) != 0)
			game->img->data[d_sp->y * game->cub_info\
					->scr_width + d_sp->stripe] = d_sp->color;
		d_sp->y++;
	}
}

static void	draw_sprite(t_game *game, t_draw_sprite *d_sp, t_ray *ray)
{
	d_sp->stripe = d_sp->draw_start_x;
	while (d_sp->stripe < d_sp->draw_end_x)
	{
		d_sp->tex_x = (int)((256 * (d_sp->stripe - (-d_sp->sprite_width / 2
				+ d_sp->sprite_screen_x)) * game->cub_info->textures[4]\
				->img_width / d_sp->sprite_width) / 256);
		if (d_sp->transform_y > 0 && d_sp->stripe > 0
			&& d_sp->stripe < game->cub_info->scr_width
			&& d_sp->transform_y < ray->z_buffer[d_sp->stripe])
			draw_sprite_y(game, d_sp);
		d_sp->stripe++;
	}
}

void		sprite_casting(t_game *game, t_ray *ray)
{
	int				i;
	t_draw_sprite	d_sp;

	d_sp.u_div = 1;
	d_sp.v_div = 1;
	d_sp.v_move = 0.0;
	i = 0;
	while (i < game->num_sprite)
	{
		game->sprites[i].distance =
			(pow((game->player->posx - game->sprites[i].x), 2)
			+ pow((game->player->posy - game->sprites[i].y), 2));
		i++;
	}
	sort_sprites(game, game->num_sprite);
	i = 0;
	while (i < game->num_sprite)
	{
		transform_sprite(game, &d_sp, i);
		calculate_sprite(game, &d_sp);
		draw_sprite(game, &d_sp, ray);
		i++;
	}
}
