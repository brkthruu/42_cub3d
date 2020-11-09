/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:44:00 by hjung             #+#    #+#             */
/*   Updated: 2020/11/09 21:22:58 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		capture_bmp(t_game *game)
{
	int			fd;
	int			f_size;
	int			pad;

	pad = (4 - (game->cub_info->scr_width * 3) % 4) % 4;
	f_size = 54 + (((3 * game->cub_info->scr_width) + pad))
								* game->cub_info->scr_height;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777)) < 0)
		return (1);
	if (save_header(game, fd, f_size))
		return (1);
	if (save_data(game, fd, pad))
		return (1);
	close(fd);
	return (0);
}

int		save_header(t_game *game, int fd, int f_size)
{
	int				i;
	unsigned char	header[54];

	i = 0;
	while (i < 54)
		header[i++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	write_4bytes(header + 2, f_size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	write_4bytes(header + 18, game->cub_info->scr_width);
	write_4bytes(header + 22, game->cub_info->scr_height);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return ((write(fd, header, 54) < 0));
}

int		save_data(t_game *game, int fd, int pad)
{
	unsigned char	padding[3];
	int				i;
	int				j;
	int				color;

	i = game->cub_info->scr_height - 1;
	padding[0] = 0;
	padding[1] = 0;
	padding[2] = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < game->cub_info->scr_width)
		{
			color = get_color(game, j, i);
			if (write(fd, &color, 3) < 0)
				return (1);
			if (pad > 0 && write(fd, &padding, pad) < 0)
				return (1);
			j++;
		}
		i--;
	}
	return (0);
}

int		get_color(t_game *game, int x, int y)
{
	int		rgb;
	int		color;

	color = game->img->data[y * game->cub_info->scr_width + x];
	rgb = (color & 0xFFFFFF);
	return (rgb);
}

void	write_4bytes(unsigned char *bytes, int value)
{
	bytes[0] = (unsigned char)(value);
	bytes[1] = (unsigned char)(value >> 8);
	bytes[2] = (unsigned char)(value >> 16);
	bytes[3] = (unsigned char)(value >> 24);
}
