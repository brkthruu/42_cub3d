/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:13:50 by hjung             #+#    #+#             */
/*   Updated: 2020/11/02 18:13:52 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	copy_map_data(t_game *game, char *buf_map)
{
	int		row;
	int		i;
	int		j;

	if (!(game->cub_info->map = malloc(sizeof(char *) * game->cub_info->rows)))
		return (0);
	row = 0;
	i = 0;
	while (row < game->cub_info->rows)
	{
		if (!(game->cub_info->map[row] = (char *)malloc(game->cub_info->cols)))
			return (0);
		ft_bzero(game->cub_info->map[row], game->cub_info->cols);
		j = 0;
		while (buf_map[i] != '\n')
		{
			game->cub_info->map[row][j] = buf_map[i];
			i++;
			j++;
		}
		row++;
		i++;
	}
	return (1);
}

int			generate_buf_map(t_game *game, char *line, char **buf_map)
{
	*buf_map = ft_strjoin(*buf_map, line);
	*buf_map = ft_strjoin(*buf_map, "\n");
	game->cub_info->rows += 1;
	if (ft_strlen(line) > game->cub_info->cols)
		game->cub_info->cols = ft_strlen(line);
	return (1);
}
