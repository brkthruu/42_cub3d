/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_map_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:36:16 by hjung             #+#    #+#             */
/*   Updated: 2020/11/02 14:26:47 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	chk_map_validity_space(t_game *game, int i, int j)
{
	if (i == 0)
	{
		if (game->cub_info->map[i][j + 1] == '0' || game->cub_info->map[i + 1][j] == '0')
			return (0);
	}
	else if (j == 0)
	{
		if (game->cub_info->map[i][j + 1] == '0' || game->cub_info->map[i + 1][j] == '0')
			return (0);
	}
	else if (i == game->cub_info->rows - 1)
	{
		if (game->cub_info->map[i][j - 1] == '0' || game->cub_info->map[i - 1][j] == '0')
			return (0);
	}
	else
	{
		if (game->cub_info->map[i][j - 1] == '0' || game->cub_info->map[i - 1][j] == '0'
			|| game->cub_info->map[i][j + 1] == '0' || game->cub_info->map[i + 1][j] == '0')
			return (0);
	}
	return (1);
}

static int	chk_map_validity_edge(t_game *game)
{
	int		i;
	int		j;
	char	**map_buffer;

	i = 0;
	j = 0;
	while (i < game->cub_info->rows)
	{
		j = 0;
		while (j < ft_strlen(game->cub_info->map[i]))
		{
			if ((i == 0 || j == 0) && game->cub_info->map[i][j] == '0')
				return (0);
			if (game->cub_info->map[i][ft_strlen(game->cub_info->map[i]) - 1] == '0')
			{
				printf("error location : line %d\n", i);
				return (0);
			}
			if (game->cub_info->map[game->cub_info->rows - 1][j] == '0')
			{
				printf("error location : %d %d\n", i, j);
				return (0);
			}
			if (game->cub_info->map[i][j] == ' ' && !chk_map_validity_space(game, i, j))
			{
				printf("error location : %d %d\n", i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	chk_map_validity(t_game *game)
{
	int	ret;

	ret = chk_map_validity_edge(game);
	return (ret);
}