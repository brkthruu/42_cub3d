/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 19:03:25 by hjung             #+#    #+#             */
/*   Updated: 2020/11/12 19:07:25 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_sprite(t_game *game, t_ray *ray)
{
	if (ray->z_buffer != 0)
	{
		free(ray->z_buffer);
		ray->z_buffer = 0;
	}
	if (game->sprites != 0)
	{
		free(game->sprites);
		game->sprites = 0;
	}
}