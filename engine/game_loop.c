/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:07:22 by hjung             #+#    #+#             */
/*   Updated: 2020/11/08 18:21:20 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
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
	ray->line_height = (int)(game->cub_info->scr_height / ray->perp_wall_dist);
}

void		calc(t_game *game, t_ray *ray)
{
	int	x;

	x = 0;
	
	//FLOOR CASTING
	floor_ceiling(game);
	
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