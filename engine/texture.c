/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:04:33 by hjung             #+#    #+#             */
/*   Updated: 2020/11/08 18:17:44 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		draw(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
							game->img->img_ptr, 0, 0);
}

void		floor_ceiling(t_game *game)
{
	int		x;
	int		y;
	int		height;
	int		width;

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

static int	x_coord_on_tex(
	t_game *game, t_ray *ray,
	double wall_x, int *tex_index)
{
	int		tex_x;

	if (ray->side == 1)
	{
		if (ray->raydir_y < 0)
			*tex_index = 0;
		else
			*tex_index = 1;
	}
	else
	{
		if (ray->raydir_x < 0)
			*tex_index = 2;
		else
			*tex_index = 3;		
	}

	tex_x = (int)(wall_x * (double)game->cub_info->textures[*tex_index]->img_width);
	if (ray->side == 0 && ray->raydir_x > 0)
		tex_x = game->cub_info->textures[*tex_index]->img_width - tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		tex_x = game->cub_info->textures[*tex_index]->img_width - tex_x - 1;
	return (tex_x);
}

void 		adjust_texture(t_game *game, t_ray *ray, int x)
{
    int		tex_index;
	int		tex_x;
	double	wall_x;

    if (ray->side == 0)
        wall_x = game->player->posy + ray->perp_wall_dist * ray->raydir_y;
    else
        wall_x = game->player->posx + ray->perp_wall_dist * ray->raydir_x;
    wall_x -= floor(wall_x);
    tex_x = x_coord_on_tex(game, ray, wall_x, &tex_index);

    // How much to increase the texture coordinate perscreen pixel
    double step = 1.0 * game->cub_info->textures[tex_index]->img_height / ray->line_height;
    // Starting texture coordinate
    double texPos = (ray->draw_start - game->cub_info->textures[tex_index]->img_height / 2 + ray->line_height / 2) * step;
    for (int y = ray->draw_start; y < ray->draw_end; y++)
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (game->cub_info->textures[tex_index]->img_height - 1);
        texPos += step;
        int color = game->cub_info->textures[tex_index]->data[game->cub_info->textures[tex_index]->img_height * texY + tex_x];
        // make color darker for y-ray->sides: R, G and B byte each divided through two with a "shift" and an "and"
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
        game->img->data[y * game->cub_info->scr_width + x] = color;
    }
}
