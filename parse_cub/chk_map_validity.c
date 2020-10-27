/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_map_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:36:16 by hjung             #+#    #+#             */
/*   Updated: 2020/10/27 20:13:24 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	chk_map_validity_space(t_map_info *map_info, int i, int j)
{
	if (i == 0)
	{
		if (map_info->map[i][j + 1] == '0' || map_info->map[i + 1][j] == '0')
			return (0);
	}
	else if (j == 0)
	{
		if (map_info->map[i][j + 1] == '0' || map_info->map[i + 1][j] == '0')
			return (0);
	}
	else if (i == map_info->rows - 1)
	{
		if (map_info->map[i][j - 1] == '0' || map_info->map[i - 1][j] == '0')
			return (0);
	}
	else
	{
		if (map_info->map[i][j - 1] == '0' || map_info->map[i - 1][j] == '0'
			|| map_info->map[i][j + 1] == '0' || map_info->map[i + 1][j] == '0')
			return (0);
	}
	return (1);
}

static int	chk_map_validity_edge(t_map_info *map_info)
{
	int		i;
	int		j;
	char	**map_buffer;

	i = 0;
	j = 0;
	while (i < map_info->rows)
	{
		j = 0;
		while (j < ft_strlen(map_info->map[i]))
		{
			if ((i == 0 || j == 0) && map_info->map[i][j] == '0')
				return (0);
			if (i == 0 && map_info->map[i][ft_strlen(map_info->map[i]) - 1] == '0')
				return (0);
			if (map_info->map[map_info->rows - 1][j] == '0')
				return (0);
			if (map_info->map[i][j] == ' ' && !chk_map_validity_space(map_info, i, j))
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

int	chk_map_validity(t_map_info *map_info)
{
	int	ret;

	ret = chk_map_validity_edge(map_info);
	return (ret);
}