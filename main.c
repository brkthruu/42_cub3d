#include "./mlx/mlx.h"
#include "cub3d.h"

void	param_init(t_param *param)
{
	param->x = 3;
	param->y = 0;
	param->str[0] = 'a';
	param->str[1] = 'b';
	param->str[2] = '\0';
}

int		key_press(int keycode, t_param *param)
{
	if (keycode == KEY_W)
		param->x++;
	else if (keycode == KEY_S)
		param->x--;
	else if (keycode == KEY_ESC)
		exit(0);
	printf("x: %d\n", param->x);
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_param	param;

	param_init(&param);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "hello world");
	mlx_hook(win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_loop(mlx_ptr);
}
