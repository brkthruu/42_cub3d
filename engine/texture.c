/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:04:33 by hjung             #+#    #+#             */
/*   Updated: 2020/11/08 20:59:07 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			coloring_floor_ceiling(t_game *game)
{
	int			x;
	int			y;
	int			height;
	int			width;

	height = game->cub_info->scr_height;
	width = game->cub_info->scr_width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			game->img->data[y * game->cub_info->scr_width + x] =
											game->cub_info->color_floor;
			game->img->data[(height - y - 1) * width + x] =
											game->cub_info->color_ceil;
			x++;
		}
		y++;
	}
}

static int		x_coord_on_tex(t_game *game, t_ray *ray, t_teximg *tximg)
{
	int			tex_x;

	if (ray->side == 1)
	{
		if (ray->raydir_y < 0)
			tximg->tex_index = 0;
		else
			tximg->tex_index = 1;
	}
	else
	{
		if (ray->raydir_x < 0)
			tximg->tex_index = 2;
		else
			tximg->tex_index = 3;
	}
	tex_x = (int)(tximg->wall_x * \
				(double)game->cub_info->textures[tximg->tex_index]->img_width);
	if (ray->side == 0 && ray->raydir_x > 0)
		tex_x = game->cub_info->textures[tximg->tex_index]\
										->img_width - tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		tex_x = game->cub_info->textures[tximg->tex_index]\
										->img_width - tex_x - 1;
	return (tex_x);
}

static void		color_to_buf(t_game *game, t_ray *ray, t_teximg *tximg, int x)
{
	int			y;
	int			color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tximg->tex_y = (int)tximg->tex_pos &
				(game->cub_info->textures[tximg->tex_index]->img_height - 1);
		tximg->tex_pos += tximg->step;
		color = game->cub_info->textures[tximg->tex_index]->data[game->cub_info
					->textures[tximg->tex_index]->img_height
					* tximg->tex_y + tximg->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		game->img->data[y * game->cub_info->scr_width + x] = color;
		y++;
	}
}

void			adjust_texture(t_game *game, t_ray *ray, int x)
{
	t_teximg	tximg;

	if (ray->side == 0)
		tximg.wall_x = game->player->posy + ray->perp_wall_dist * ray->raydir_y;
	else
		tximg.wall_x = game->player->posx + ray->perp_wall_dist * ray->raydir_x;
	tximg.wall_x -= floor(tximg.wall_x);
	tximg.tex_x = x_coord_on_tex(game, ray, &tximg);
	tximg.step = 1.0 * game->cub_info->textures[tximg.tex_index]->img_height
					/ ray->line_height;
	tximg.tex_pos = (ray->draw_start - game->cub_info
					->textures[tximg.tex_index]->img_height / 2
					+ ray->line_height / 2) * tximg.step;
	color_to_buf(game, ray, &tximg, x);
}
