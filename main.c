#include <string.h>
#include "../mlx/mlx.h"
#include "./cub3d.h"

# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))

//Draw the line by DDA algorithm
void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img->data[TO_COORD(x1, y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < COLS)
	{
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
		i++;
	}
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
		j++;
	}
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
}

void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img->data[(y  + i) * WIDTH + x + j] = 0x008080;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (game->cub_info->map[i][j] == 1)
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
}

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

void	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "mlx 42");
}

int	init_textures(t_game *game, int nbr_textures)
{
	int count;

	count = 0;
	if (!(game->cub_info->textures = malloc(sizeof(t_img *) * nbr_textures )))
		return (0);
	while (count < nbr_textures)
	{
		if (!(game->cub_info->textures[count] = malloc(sizeof(t_img))))
			return (0);
		ft_bzero(game->cub_info->textures[count], sizeof(t_img));
		count++;
	}
	return (1);
}

void	init_cub_info(t_game *game)
{
	game->cub_info = malloc(sizeof(t_cub_info));
}
   
void	img_init(t_game *game)
{
	game->img->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	game->img->data = mlx_get_data_addr(game->img->img_ptr, &game->img->bpp, &game->img->size_l, &game->img->endian);
}

int		main_loop(t_game *game)
{

	draw_rectangles(game);
	draw_lines(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->img_ptr, 0, 0);
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

int		main(void)
{
	t_game	game;
	int		parse;
	int		i;
	int		j;

	init_game(&game);
	// img_init(&game);
	// mlx_hook(game.win_ptr, X_EVENT_KEY_PRESS, 0, &deal_key, &game);
	// mlx_hook(game.win_ptr, X_EVENT_KEY_EXIT, 0, &close_window, &game);

	init_cub_info(&game);
	if (!init_textures(&game, 4))
		printf("texture initialize err\n");
	parse = parse_config(&game);
	printf("parsed screenWidth: %d\n", game.cub_info->screenWidth);
	printf("parsed screenHeight: %d\n", game.cub_info->screenHeight);
	printf("floor color: %d\n", game.cub_info->color_floor);
	printf("ceil color: %d\n", game.cub_info->color_ceil);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.cub_info->textures[0]->img_ptr, 0, 0);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.cub_info->textures[1]->img_ptr, 50, 50);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.cub_info->textures[2]->img_ptr, 70, 70);
	mlx_put_image_to_window(game.mlx_ptr, game.win_ptr, game.cub_info->textures[3]->img_ptr, 100, 100);

	i = 0;
	j = 0;
	/*
	for (i = 0 ; i < game.cub_info->screenHeight ; i++)
	{
		for (j = 0; j < game.cub_info->screenWidth; j++)
			printf("%d", game.cub_info->map[i][j]);
		printf("\n");
	}
	*/	
	// mlx_loop_hook(game.mlx_ptr, &main_loop, &game);
	 mlx_loop(game.mlx_ptr);

	return (0);	
}
