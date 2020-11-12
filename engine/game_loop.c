/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:07:22 by hjung             #+#    #+#             */
/*   Updated: 2020/11/12 19:08:06 by hjung            ###   ########.fr       */
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
		if (game->cub_info->map[ray->map_y][ray->map_x] == '1')
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
	sprite_casting(game, ray);
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
	free_sprite(game, &ray);
	return (1);
}
