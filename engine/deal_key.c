/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 21:21:50 by hjung             #+#    #+#             */
/*   Updated: 2020/11/11 20:11:04 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_game *game)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = game->player->dir_x;
	oldplane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x
			* cos(-game->player->rotate_speed) - game->player->dir_y
			* sin(-game->player->rotate_speed);
	game->player->dir_y = olddir_x * sin(-game->player->rotate_speed)
			+ game->player->dir_y * cos(-game->player->rotate_speed);
	game->player->plane_x = game->player->plane_x
			* cos(-game->player->rotate_speed) - game->player->plane_y
			* sin(-game->player->rotate_speed);
	game->player->plane_y = oldplane_x * sin(-game->player->rotate_speed)
			+ game->player->plane_y * cos(-game->player->rotate_speed);
}

void	rotate_right(t_game *game)
{
	double olddir_x;
	double oldplane_x;

	olddir_x = game->player->dir_x;
	oldplane_x = game->player->plane_x;
	game->player->dir_x = game->player->dir_x
			* cos(game->player->rotate_speed) - game->player->dir_y
			* sin(game->player->rotate_speed);
	game->player->dir_y = olddir_x * sin(game->player->rotate_speed)
			+ game->player->dir_y * cos(game->player->rotate_speed);
	game->player->plane_x = game->player->plane_x
			* cos(game->player->rotate_speed) - game->player->plane_y
			* sin(game->player->rotate_speed);
	game->player->plane_y = oldplane_x * sin(game->player->rotate_speed)
			+ game->player->plane_y * cos(game->player->rotate_speed);
}

int		key_press(int key, t_game *game)
{
	if (key == KEY_W)
		move_forward(game);
	if (key == KEY_S)
		move_backward(game);
	if (key == KEY_A)
		move_left(game);
	if (key == KEY_D)
		move_right(game);
	if (key == KEY_LEFT)
		rotate_left(game);
	if (key == KEY_RIGHT)
		rotate_right(game);
	if (key == KEY_ESC)
		exit(0);
	return (0);
}
