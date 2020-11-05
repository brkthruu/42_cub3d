/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_map_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:36:16 by hjung             #+#    #+#             */
/*   Updated: 2020/11/05 19:35:01 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	set_player(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player->dir_y = -1.0;
		game->player->plane_x = 0.66;
		game->player->plane_y = 0.0;
	}
	else if (c == 'S')
	{
		game->player->dir_y = 1.0;
		game->player->plane_x = -0.66;
		game->player->plane_y = 0.0;
	}
	else if (c == 'E')
	{
		game->player->dir_x = 1.0;
		game->player->plane_x = 0.0;
		game->player->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		game->player->dir_x = -1.0;
		game->player->plane_x = 0.0;
		game->player->plane_y = -0.66;
	}
}

static int	parse_player_info(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->cub_info->rows)
	{
		j = 0;
		while (j < game->cub_info->cols)
		{
			if (game->cub_info->map[i][j] == 'N'
				|| game->cub_info->map[i][j] == 'S'
				|| game->cub_info->map[i][j] == 'W'
				|| game->cub_info->map[i][j] == 'E')
			{
				printf("parsed start direction: %c\n", game->cub_info->map[i][j]);
				game->player->posx = (double)j;
				game->player->posy = (double)i;
				set_player(game, game->cub_info->map[i][j]);
			}
			j++;
		}
		i++;
	}
	if (game->player->posx < 0)
		return (0);
	return (1);
}

static int	chk_map_validity_space(t_game *game, int i, int j)
{
	if (i == 0 || j == 0)
	{
		if (game->cub_info->map[i][j + 1] == '0'
			|| game->cub_info->map[i + 1][j] == '0')
			return (0);
	}
	else if (i == game->cub_info->rows - 1)
	{
		if (game->cub_info->map[i][j - 1] == '0'
			|| game->cub_info->map[i - 1][j] == '0')
			return (0);
	}
	else
	{
		if (game->cub_info->map[i][j - 1] == '0'
			|| game->cub_info->map[i - 1][j] == '0'
			|| game->cub_info->map[i][j + 1] == '0'
			|| game->cub_info->map[i + 1][j] == '0')
			return (0);
	}
	return (1);
}

static int	chk_map_validity_edge(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->cub_info->rows)
	{
		j = 0;
		while (j < game->cub_info->cols)
		{
			if ((i == 0 || j == 0) && game->cub_info->map[i][j] == '0')
				return (0);
			if (game->cub_info->map[game->cub_info->rows - 1][j] == '0')
				return (0);
			if ((game->cub_info->map[i][j] == ' '
				|| game->cub_info->map[i][j] == 0)
				&& !chk_map_validity_space(game, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			chk_map_validity(t_game *game)
{
	if (!chk_map_validity_edge(game))
		return (0);
	if (!parse_player_info(game))
		return (0);
	return (1);
}
