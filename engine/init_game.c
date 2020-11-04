/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:45:00 by hjung             #+#    #+#             */
/*   Updated: 2020/11/04 11:58:31 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int init_player(t_game *game)
{
    if (!(game->player = malloc(sizeof(t_player))))
        return (0);
    game->player->posx = -1.0;
	game->player->dir_x = 0.0;
	game->player->dir_y = 0.0;
	game->player->speed = 0.4;
	game->player->rotate_speed = 0.4;
    return (1);
}

int	init_cub_info(t_game *game)
{
    if (!(game->cub_info = malloc(sizeof(t_cub_info))))
        return (0);
	game->cub_info->rows = 0;
	game->cub_info->cols = 0;
    return (1);
}

int	init_textures(t_game *game, int nbr_textures)
{
	int count;

	count = 0;
	if (!(game->cub_info->textures = malloc(sizeof(t_img *) * nbr_textures )))
		return (0);
	while (count < nbr_textures)
	{
		if (!(game->cub_info->textures[count] = malloc(sizeof(t_img))))
			return (0);
		ft_bzero(game->cub_info->textures[count], sizeof(t_img));
		count++;
	}
	return (1);
}