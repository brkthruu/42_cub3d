/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 21:21:50 by hjung             #+#    #+#             */
/*   Updated: 2020/11/08 21:46:21 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int key, t_game *game)
{
	printf("current positon : %d %d\n", (int)game->player->posx, (int)game->player->posy);
	printf("CUR DIRECTION : %lf %lf\n", game->player->dir_x, game->player->dir_y);
	if (key == KEY_W)
	{
		if (game->cub_info->map[(int)(game->player->posy)][(int)(game->player->posx + game->player->dir_x * game->player->speed)] == '0')
			game->player->posx += game->player->dir_x * game->player->speed;
		if (game->cub_info->map[(int)(game->player->posy + game->player->dir_y * game->player->speed)][(int)(game->player->posx)] == '0')
			game->player->posy += game->player->dir_y * game->player->speed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (game->cub_info->map[(int)(game->player->posy)][(int)(game->player->posx - game->player->dir_x * game->player->speed)] == '0')
			game->player->posx -= game->player->dir_x * game->player->speed;
		if (game->cub_info->map[(int)(game->player->posy - game->player->dir_y * game->player->speed)][(int)(game->player->posx)] == '0')
			game->player->posy -= game->player->dir_y * game->player->speed;
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x
			* cos(-game->player->rotate_speed) - game->player->dir_y
			* sin(-game->player->rotate_speed);
		game->player->dir_y = oldDirX * sin(-game->player->rotate_speed) + game->player->dir_y * cos(-game->player->rotate_speed);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-game->player->rotate_speed) - game->player->plane_y * sin(-game->player->rotate_speed);
		game->player->plane_y = oldPlaneX * sin(-game->player->rotate_speed) + game->player->plane_y * cos(-game->player->rotate_speed);
	}
	//rotate to the right
	if (key == KEY_D)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(game->player->rotate_speed) - game->player->dir_y * sin(game->player->rotate_speed);
		game->player->dir_y = oldDirX * sin(game->player->rotate_speed) + game->player->dir_y * cos(game->player->rotate_speed);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(game->player->rotate_speed) - game->player->plane_y * sin(game->player->rotate_speed);
		game->player->plane_y = oldPlaneX * sin(game->player->rotate_speed) + game->player->plane_y * cos(game->player->rotate_speed);
	}
	// if (key == KEY_ESC)
	// 	exit(0);
	return (0);
}

int		key_release(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	// else if (key == KEY_W)
	// 	info->key_w = 0;
	// else if (key == KEY_A)
	// 	info->key_a = 0;
	// else if (key == KEY_S)
	// 	info->key_s = 0;
	// else if (key == KEY_D)
	// 	info->key_d = 0;
	return (0);
}