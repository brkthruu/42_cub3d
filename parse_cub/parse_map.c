/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:13:50 by hjung             #+#    #+#             */
/*   Updated: 2020/10/27 16:40:05 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_map_validity(t_map_info *map_info)
{
	int		i;
	int		j;
	char	**map_buffer;

	i = 0;
	j = 0;
	printf("%p\n", &map_info->rows);
	printf("%p\n", &map_info->cols);
	printf("%p\n", map_info->map);
	while (i < map_info->rows)
	{
		j = 0;
		while (j < map_info->cols)
		{
			j++;
		}
		i++;
	}
	return (1);
}

static void	parse_map_data(t_map_info *map_info)
{
	int		i;
	int		ret;
	int		fd;
	char	*line;

	map_info->map = (char **)malloc(sizeof(char *) * map_info->rows);
	fd = open("map/map.cub", O_RDONLY);
	i = 0;
	while (fd >= 0 && (ret = get_next_line(fd, &line)) > 0)
	{
		map_info->map[i] = (char *)malloc(sizeof(char) * map_info->cols);
		map_info->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	map_info->map[i] = (char *)malloc(sizeof(char) * map_info->cols);
	free(line);
	close(fd);
}

static void	get_map_size(t_map_info *map_info)
{
	int		ret;
	int		fd;
	char	*line;

	map_info->rows = 0;
	map_info->cols = 0;
	fd = open("map/map.cub", O_RDONLY);
	while (fd >= 0 && (ret = (get_next_line(fd, &line)) > 0))
	{
		if (ft_strlen(line) > map_info->cols)
			map_info->cols = ft_strlen(line);
		map_info->rows += 1;
		free(line);
	}
	if (ft_strlen(line) > map_info->cols)
		map_info->cols = ft_strlen(line);
	map_info->rows += 1;
	free(line);
	close(fd);
}

int	parse_map(t_map_info *map_info)
{
	int a = 0;

	get_map_size(map_info);
	parse_map_data(map_info);
	a = check_map_validity(map_info);
	return (a);
}
