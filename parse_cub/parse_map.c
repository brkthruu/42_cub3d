/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:13:50 by hjung             #+#    #+#             */
/*   Updated: 2020/11/01 18:25:53 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	copy_line_data(char *map_info, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		map_info[i] = line[i];
		i++;
	}
}

static void	parse_map_data(t_game *game)
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
		ft_bzero(map_info->map[i], map_info->cols);
		copy_line_data(map_info->map[i], line);
		free(line);
		i++;
	}
	map_info->map[i] = (char *)malloc(sizeof(char) * map_info->cols);
	ft_bzero(map_info->map[i], map_info->cols);
	copy_line_data(map_info->map[i], line);
	free(line);
	close(fd);
}

static void	get_map_size(t_game *game)
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

int	parse_map(t_game *game)
{
	int a = 0;

	get_map_size(game);
	parse_map_data(game);
	a = chk_map_validity(game);
	printf("valid map : %s\n", a ? "True" : "False");
	return (a);
}
