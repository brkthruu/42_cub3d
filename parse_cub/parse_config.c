/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:31:12 by hjung             #+#    #+#             */
/*   Updated: 2020/10/29 19:45:04 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../cub3d.h"

static int parse_scr_size(t_cub_info *cub_info, char *line)
{
	int		i;

	i = 2;
	if (!is_whitespace(line[1]))
		return (0);
	cub_info->screenWidth = ft_atoi(ft_strchr(line, ' ') + 1);
	while (!is_whitespace(line[i]))
	{
		if (!line[i])
			return (0);
		i++;
	}
	cub_info->screenHeight = ft_atoi(&line[i] + 1);
	return (1);
}

static int	classify(t_cub_info *cub_info, char *line)
{
	if (line[0] == 'R')
		return (parse_scr_size(cub_info, line));
	return (1);

}

int	parse_map(t_game *game, t_cub_info *map_info)
{
	int		ret;
	int		fd;
	char	*line;

	fd = open("map/map.cub", O_RDONLY);
	while (fd >= 0 && (ret = (get_next_line(fd, &line)) > 0))
	{
		printf("%s\n", line);
		if (classify(map_info, line) == 0)
			leave(1, game, "map parsing err\n");
		free(line);
	}
	free(line);
	close(fd);

	return (0);
}