/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:07:22 by hjung             #+#    #+#             */
/*   Updated: 2020/11/04 12:04:40 by hjung            ###   ########.fr       */
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
	while (x < game->cub_info->scr_width)
	{
		init_ray(game, ray, x);
		calc_side_dist(game, ray);
		
		while (ray->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
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
			//Check if ray has hit a wall
			if (game->cub_info->map[ray->map_x][ray->map_y] > '0')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - game->player->posx + (1 - ray->step_x) / 2) / ray->raydir_x;
		else
			ray->perp_wall_dist = (ray->map_y - game->player->posy + (1 - ray->step_y) / 2) / ray->raydir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(game->cub_info->scr_height / ray->perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->cub_info->scr_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + game->cub_info->scr_height / 2;
		if(drawEnd >= game->cub_info->scr_height)
			drawEnd = game->cub_info->scr_height - 1;

		int	color;
		if (game->cub_info->map[ray->map_x][ray->map_y] == '1')
			color = 0xFF0000;
		else if (game->cub_info->map[ray->map_x][ray->map_y] == '2')
			color = 0x00FF00;
		else if (game->cub_info->map[ray->map_x][ray->map_y] == '3')
			color = 0x0000FF;
		else if (game->cub_info->map[ray->map_x][ray->map_y] == '4')
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		if (ray->side == 1)
			color = color / 2;

		verLine(game, x, drawStart, drawEnd, color);
		
		x++;
	}
}

int		game_loop(t_game *game)
{
	t_ray	ray;
	calc(game, &ray);
	return (0);
}