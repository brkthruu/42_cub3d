/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:52:36 by hjung             #+#    #+#             */
/*   Updated: 2020/11/09 21:57:24 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    move_forward(t_game *game)
{
    if (game->cub_info->map[(int)(game->player->posy)][(int)(game->player->posx + game->player->dir_x * game->player->speed)] == '0')
        game->player->posx += game->player->dir_x * game->player->speed;
    if (game->cub_info->map[(int)(game->player->posy + game->player->dir_y * game->player->speed)][(int)(game->player->posx)] == '0')
        game->player->posy += game->player->dir_y * game->player->speed;
}

void    move_backward(t_game *game)
{
    if (game->cub_info->map[(int)(game->player->posy)]
        [(int)(game->player->posx - game->player->dir_x
        * game->player->speed)] == '0')
        game->player->posx -= game->player->dir_x * game->player->speed;
    if (game->cub_info->map[(int)(game->player->posy - game->player->dir_y
        * game->player->speed)][(int)(game->player->posx)] == '0')
        game->player->posy -= game->player->dir_y * game->player->speed;
}

void    move_left(t_game *game)
{
    if (game->cub_info->map[(int)game->player->posy][(int)(game->player->posx - game->player->plane_x * game->player->speed)] == '0')
        game->player->posx -= game->player->plane_x	* game->player->speed;
    if (game->cub_info->map[(int)(game->player->posy - game->player->plane_y * game->player->speed)][(int)game->player->posx] == '0')
        game->player->posy -= game->player->plane_y	* game->player->speed;
}

void    move_right(t_game *game)
{
    if (game->cub_info->map[(int)game->player->posy]
		[(int)(game->player->posx + game->player->plane_x
		* game->player->speed)] == '0')
		game->player->posx += game->player->plane_x * game->player->speed;
	if (game->cub_info->map[(int)(game->player->posy
		+ game->player->plane_y * game->player->speed)]
		[(int)game->player->posx] == '0')
		game->player->posy += game->player->plane_y * game->player->speed;
}
