/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_config_validity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:14:28 by hjung             #+#    #+#             */
/*   Updated: 2020/11/12 15:32:30 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	chk_config_validity(t_game *game, t_cub_info *cub_info)
{
	int i;

	i = 0;
	if (cub_info->scr_width < 0 || cub_info->scr_height < 0)
		return (0);
	if (cub_info->scr_width > 1920)
		cub_info->scr_width = 1920;
	if (cub_info->scr_height > 1080)
		cub_info->scr_height = 1080;
	while (i < 4)
	{
		if (cub_info->textures[i]->size_l < 0)
			return (0);
		i++;
	}
	if (cub_info->textures[4]->size_l < 0 && game->num_sprite > 0)
		leave(1, game, "ERROR\nNo sprite texture provided");
	if (game->cub_info->color_floor == -1
		|| game->cub_info->color_ceil == -1)
		leave(1, game, "ERROR\nNo color data provided");
	return (1);
}
