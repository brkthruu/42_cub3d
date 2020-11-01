/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:31:12 by hjung             #+#    #+#             */
/*   Updated: 2020/11/01 18:25:48 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_texture(t_game *game, char *line, int tex_index)
{
	if (!(game->cub_info->textures[tex_index]->img_ptr =
		mlx_xpm_file_to_image(game->mlx_ptr, (char *)line,
		&game->cub_info->textures[tex_index]->img_width,
		&game->cub_info->textures[tex_index]->img_height)))
		{
			printf("return zero\n");
			return (0);
		}

	game->cub_info->textures[tex_index]->data =
		mlx_get_data_addr(game->cub_info->textures[tex_index]->img_ptr,
		&game->cub_info->textures[tex_index]->bpp,
		&game->cub_info->textures[tex_index]->size_l,
		&game->cub_info->textures[tex_index]->endian);
	return (1);
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
		return (set_texture(game, &line[3], 0));
	else if (line[0] == 'S' && line[1] == 'O')
		return (set_texture(game, &line[3], 1));
	else if (line[0] == 'W' && line[1] == 'E')
		return (set_texture(game, &line[3], 2));
	else if (line[0] == 'E' && line[1] == 'A')
		return (set_texture(game, &line[3], 3));
	else if (line[0] == 'F' || line[0] == 'C')
		return (parse_color(game, line, line[0]));
	// else if (is_map(line))
	// 	parse_map(t_game, line);
	return (1);

}

int			parse_config(t_game *game)
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