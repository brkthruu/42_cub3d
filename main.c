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
	void	*img_ptr;
	t_param	param;
	t_img	img;

	int		img_width;
	int 	img_height;

	int		idx_w;
	int		idx_h;

	//1 initialization
	param_init(&param);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "hello world");
	
	//2 key press
	mlx_hook(win_ptr, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &param);
	
	//3 load image
	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "42logo.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 150, 150);
	
	
	//4 draw image
	//new image를 생성하고 get_data_addr 함수로 해당 이미지의 주소를 받아와야 수정이 가능하다
	
	img.img_ptr = mlx_new_image(mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	//여기서 (int *)를 안해주고 img.data가 void *이면 밑에 배열값들을 참조할 때 다 4를 곱해야한다.
	//그렇기 때문에 int *로 캐스팅해주는편이 좋다고 한다.
	

	//화면을 2차원 배열로 보고 한칸씩 색을 채워나가는 코드
	idx_h = -1;
	while (++idx_h < IMG_HEIGHT)
	{
		idx_w = -1;
		while (++idx_w < IMG_WIDTH)
		{
			if (idx_w % 2)
				img.data[idx_h * IMG_WIDTH + idx_w] = 0xFFFFFF;
			else
				img.data[idx_h * IMG_WIDTH + idx_w] = 0x008080;
		}
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 0, 0);
	mlx_loop(mlx_ptr);

	return (0);
}
