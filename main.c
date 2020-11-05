#include <string.h>
#include "../mlx/mlx.h"
#include "./cub3d.h"

int 	close_window(t_game *game)
{
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

int	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!init_cub_info(game) || !init_textures(game, 4)
		|| !init_player(game))
		return (0);
	if (!parse_config(game))
		leave(1, game, "invalid map\n");
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->cub_info->scr_width, \
									game->cub_info->scr_height, "CUB3D");
	if (!init_image(game))
		return (0);
	return (1);
}

int	deal_key(int key, t_game *game)
{
	printf("current positon : %lf %lf\n", game->player->posx, game->player->posy);
	printf("current direction : %lf %lf\n", game->player->dir_x, game->player->dir_y);
	if (key == KEY_W)
	{
		if (game->cub_info->map[(int)(game->player->posx + game->player->dir_x * game->player->speed)][(int)(game->player->posy)] == '0')
			game->player->posx += game->player->dir_x * game->player->speed;
		if (game->cub_info->map[(int)(game->player->posx)][(int)(game->player->posy + game->player->dir_y * game->player->speed)] == '0')
			game->player->posy += game->player->dir_y * game->player->speed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (game->cub_info->map[(int)(game->player->posx - game->player->dir_x * game->player->speed)][(int)(game->player->posy)] == '0')
			game->player->posx -= game->player->dir_x * game->player->speed;
		if (game->cub_info->map[(int)(game->player->posx)][(int)(game->player->posy - game->player->dir_y * game->player->speed)] == '0')
			game->player->posy -= game->player->dir_y * game->player->speed;
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x
			* cos(-game->player->rotate_speed) - game->player->dir_y
			* sin(-game->player->rotate_speed);
		game->player->dir_y = oldDirX * sin(-game->player->rotate_speed) + game->player->dir_y * cos(-game->player->rotate_speed);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-game->player->rotate_speed) - game->player->plane_y * sin(-game->player->rotate_speed);
		game->player->plane_y = oldPlaneX * sin(-game->player->rotate_speed) + game->player->plane_y * cos(-game->player->rotate_speed);
	}
	//rotate to the right
	if (key == KEY_D)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(game->player->rotate_speed) - game->player->dir_y * sin(game->player->rotate_speed);
		game->player->dir_y = oldDirX * sin(game->player->rotate_speed) + game->player->dir_y * cos(game->player->rotate_speed);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(game->player->rotate_speed) - game->player->plane_y * sin(game->player->rotate_speed);
		game->player->plane_y = oldPlaneX * sin(game->player->rotate_speed) + game->player->plane_y * cos(game->player->rotate_speed);
	}
	if (key == KEY_ESC)
		exit(0);
	return (0);
}

int		main(void)
{
	t_game	game;
	int		i;
	int		j;

	if (!init_game(&game))
		return (0);
	i = 0;
	j = 0;
	for (i = 0; i < game.cub_info->rows; i++)
	{
		for (j = 0; j < game.cub_info->cols; j++)
		{
			printf("%c", game.cub_info->map[i][j]);
		}
		printf("\n");
	}
	printf("initial direction : %lf %lf\n", game.player->dir_x, game.player->dir_y);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.cub_info->textures[0]->img_ptr, 150, 150);
	mlx_loop_hook(game.mlx_ptr, &game_loop, &game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_EXIT, 0, &close_window, &game);
	mlx_loop(game.mlx_ptr);

	return (0);	
}
