/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:13:50 by hjung             #+#    #+#             */
/*   Updated: 2020/10/27 11:55:20 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	get_map_info(t_map_info *map_info)
{
	int		ret;
	int		fd;
	char	*line;
	char	*temp_map;

	map_info->rows = 0;
	map_info->cols = 0;
	map_info->map = ft_strjoin("", "");
	fd = open("map/map.cub", O_RDONLY);
	while (fd >= 0 && (ret = (get_next_line(fd, &line)) > 0))
	{
		temp_map = map_info->map;
		map_info->map = ft_strjoin(map_info->map, line);
		free(temp_map);
		if (ft_strlen(line) > map_info->cols)
			map_info->cols = ft_strlen(line);
		map_info->rows += 1;
		free(line);
	}
	temp_map = map_info->map;
	map_info->map = ft_strjoin(map_info->map, line);
	free(temp_map);
	free(line);
	close(fd);
	return (0);
}

int	parse_map(t_map_info *map_info)
{
	int a = 0;

	get_map_size(map_info);
	return (a);
}
