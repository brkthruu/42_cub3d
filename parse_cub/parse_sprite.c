/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:27:44 by hjung             #+#    #+#             */
/*   Updated: 2020/11/11 20:08:14 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	sprite_cnt(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->cub_info->rows)
	{
		j = 0;
		while (j < game->cub_info->cols)
		{
			if (game->cub_info->map[i][j] == '2')
				game->num_sprite++;
			j++;
		}
		i++;
	}
	return (1);
}
