/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:02:10 by hjung             #+#    #+#             */
/*   Updated: 2020/11/11 20:07:24 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		sort_sprites(t_game *game, int num_sprite)
{
	int				i;
	int				j;
	t_sprite		tmp;

	i = 0;
	while (i < num_sprite)
	{
		j = i + 1;
		while (j < num_sprite)
		{
			if (game->sprites[i].distance < game->sprites[j].distance)
			{
				tmp = game->sprites[i];
				game->sprites[i] = game->sprites[j];
				game->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
