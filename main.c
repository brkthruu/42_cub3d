#include <string.h>
#include "../mlx/mlx.h"
#include "./cub3d.h"

int		deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	return (0);
}

int 	close_window(t_game *game)
{
	exit(0);
	return (0);
}

void	verLine(t_game *game, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y, color);
		y++;
	}
}

void	calc(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->cub_info->scr_width)
	{
		double cameraX = 2 * x / (double)game->cub_info->scr_width - 1;
		double rayDirX = game->player->dir_x + game->player->plane_x * cameraX;
		double rayDirY = game->player->dir_x + game->player->plane_y * cameraX;
		
		int mapX = (int)game->player->pos_x;
		int mapY = (int)game->player->pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->pos_y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game->cub_info->map[mapY][mapX] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->player->pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->player->pos_y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(game->cub_info->scr_height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game->cub_info->scr_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + game->cub_info->scr_height / 2;
		if(drawEnd >= game->cub_info->scr_height)
			drawEnd = game->cub_info->scr_height - 1;

		int	color;
		if (game->cub_info->map[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (game->cub_info->map[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (game->cub_info->map[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (game->cub_info->map[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		if (side == 1)
			color = color / 2;

		verLine(game, x, drawStart, drawEnd, color);
		
		x++;
	}
}

int		main_loop(t_game *game)
{
	calc(game);
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
	return (1);
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
	mlx_loop_hook(game.mlx_ptr, &main_loop, &game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_EXIT, 0, &close_window, &game);
	mlx_loop(game.mlx_ptr);

	return (0);	
}
