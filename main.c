/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 13:22:33 by hjung             #+#    #+#             */
/*   Updated: 2020/11/12 18:13:12 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "./cub3d.h"

int		close_window(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}

void	leave(int mod, t_game *game, char *msg)
{
	if (mod == 0)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	ft_putstr_fd(msg, 1);
	if (msg[0])
		write(1, "\n", 1);
	exit(0);
}

int		init_game(t_game *game, char *argv)
{
	game->mlx_ptr = mlx_init();
	if (!init_cub_info(game) || !init_textures(game, 5)
		|| !init_player(game))
		return (0);
	game->num_sprite = 0;
	game->buf_map = (char *)malloc(sizeof(char) * 2);
	game->buf_map = "";
	if (!parse_config(game, argv))
		leave(1, game, "Error\nInvalid map");
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->cub_info->scr_width, \
									game->cub_info->scr_height, "CUB3D");
	if (!init_image(game))
		return (0);
	if (!init_sprite(game))
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
		leave(1, &game, "ERROR\nNo map file");
	if (!init_game(&game, argv[1]))
		return (0);
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
			game.save = 1;
		else
			leave(1, &game, "ERROR\nInvalid option");
	}
	mlx_loop_hook(game.mlx_ptr, &game_loop, &game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_EXIT, 0, &close_window, &game);
	mlx_loop(game.mlx_ptr);
	return (0);
}
