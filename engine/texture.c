/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:04:33 by hjung             #+#    #+#             */
/*   Updated: 2020/11/06 12:38:41 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(t_game *game)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->img_ptr, 0, 0);
}

void adjust_texture(t_game *game, t_ray *ray, int x)
{
    int texNum = 3;

    // calculate value of wallX
    double wallX;
    if (ray->side == 0)
        wallX = game->player->posy + ray->perp_wall_dist * ray->raydir_y;
    else
        wallX = game->player->posx + ray->perp_wall_dist * ray->raydir_x;
    wallX -= floor(wallX);

    // x coordinate on the texture
    int texX = (int)(wallX * (double)game->cub_info->textures[texNum]->img_width);
    if (ray->side == 0 && ray->raydir_x > 0)
        texX = game->cub_info->textures[texNum]->img_width - texX - 1;
    if (ray->side == 1 && ray->raydir_y < 0)
        texX = game->cub_info->textures[texNum]->img_width - texX - 1;

    // How much to increase the texture coordinate perscreen pixel
    double step = 1.0 * game->cub_info->textures[texNum]->img_height / ray->line_height;
    // Starting texture coordinate
    double texPos = (ray->draw_start - game->cub_info->textures[texNum]->img_height / 2 + ray->line_height / 2) * step;
    for (int y = ray->draw_start; y < ray->draw_end; y++)
    {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (game->cub_info->textures[texNum]->img_height - 1);
        texPos += step;
        int color = game->cub_info->textures[texNum]->data[game->cub_info->textures[texNum]->img_height * texY + texX];
        // make color darker for y-ray->sides: R, G and B byte each divided through two with a "shift" and an "and"
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
        game->img->data[y * game->cub_info->scr_width + x] = color;
    }
}