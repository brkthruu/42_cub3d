/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:31:12 by hjung             #+#    #+#             */
/*   Updated: 2020/10/30 13:44:47 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../cub3d.h"
static int	set_texture(t_game *game, char *line)
{
		
}

static int	parse_scr_size(t_game *game, char *line)
{
	int		i;

	i = 2;
	if (!is_whitespace(line[1]))
		return (0);
	game->cub_info->screenWidth = ft_atoi(ft_strchr(line, ' ') + 1);
	while (!is_whitespace(line[i]))
	{
		if (!line[i])
			return (0);
		i++;
	}
	game->cub_info->screenHeight = ft_atoi(&line[i] + 1);
	return (1);
}

static int	classify(t_game *game, char *line)
{
	if (line[0] == 'R')
		return (parse_scr_size(game, line));
	else if (line[0] == 'N' && line[1] == 'O')
		return (0);
	return (1);

}

int	parse_map(t_game *game)
{
	int		ret;
	int		fd;
	char	*line;

	fd = open("map/map.cub", O_RDONLY);
	while (fd >= 0 && (ret = (get_next_line(fd, &line)) > 0))
	{
		printf("%s\n", line);
		if (classify(game, line) == 0)
			leave(1, game, "map parsing err\n");
		free(line);
	}
	free(line);
	close(fd);

	return (0);
}