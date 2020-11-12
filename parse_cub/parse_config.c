/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:31:12 by hjung             #+#    #+#             */
/*   Updated: 2020/11/12 15:39:12 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_texture(t_game *game, char *line, int tex_index)
{
	int		i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (game->cub_info->textures[tex_index]->size_l != -1)
		return (0);
	if (!(game->cub_info->textures[tex_index]->img_ptr =
		mlx_xpm_file_to_image(game->mlx_ptr, (char *)&line[i],
		&game->cub_info->textures[tex_index]->img_width,
		&game->cub_info->textures[tex_index]->img_height)))
		return (0);
	game->cub_info->textures[tex_index]->data =
		(int *)mlx_get_data_addr(game->cub_info->textures[tex_index]->img_ptr,
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
	game->cub_info->scr_width = ft_atoi(ft_strchr(line, ' ') + 1);
	while (!is_whitespace(line[i]))
	{
		if (!line[i])
			return (0);
		i++;
	}
	game->cub_info->scr_height = ft_atoi(&line[i] + 1);
	return (1);
}

static int	classify(t_game *game, char *line, char **buf_map)
{
	int		i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (line[i] == 'R')
		return (parse_scr_size(game, line));
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (set_texture(game, &line[i + 3], 0));
	else if (line[i] == 'S' && line[i + 1] == 'O')
		return (set_texture(game, &line[i + 3], 1));
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (set_texture(game, &line[i + 3], 2));
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (set_texture(game, &line[i + 3], 3));
	else if (line[i] == 'S' && line[i + 1] == ' ')
		return (set_texture(game, &line[i + 2], 4));
	else if (line[i] == 'F' || line[i] == 'C')
		return (parse_color(game, line, line[i]));
	else if (line[i] == '1' || line[i] == ' ' || line[i] == '0'
			|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E' || line[i] == '2')
		return (generate_buf_map(game, line, buf_map));
	return (1);
}

int			parse_config(t_game *game, char *argv)
{
	int		ret;
	int		fd;
	char	*line;
	char	*buf_map;

	buf_map = malloc(sizeof(char) * 2);
	buf_map = "";
	if ((fd = open(argv, O_RDONLY)) < 0)
		leave(1, game, "ERROR\nNo such file\n");
	while (fd >= 0 && (ret = (get_next_line(fd, &line))) != -1)
	{
		if (classify(game, line, &buf_map) == 0)
			leave(1, game, "ERROR\nMap info parsing err");
		free(line);
		if (ret == 0)
			break ;
	}
	close(fd);
	if (!copy_map_data(game, buf_map) || !chk_map_validity(game)
		|| !chk_config_validity(game, game->cub_info))
		return (0);
	return (1);
}
