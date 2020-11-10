/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:42:44 by hjung             #+#    #+#             */
/*   Updated: 2020/11/10 19:31:40 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_sprites(t_game *game, int num_sprite)
{
    int         i;
    int         j;
    t_sprite    tmp;

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