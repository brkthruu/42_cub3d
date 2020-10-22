#include "./mlx/mlx.h"

int main()
{
	/* mlx_init() 함수는 void *를 리턴한다.
	 * graphical server 와 연결하기 위함이다.
	 */
	void *mlx_ptr;
	void *win_ptr;

	/* 아래 3개의 함수는 필수적이다 */
	mlx_ptr = mlx_init();
	/* 매개변수에 대해서는 mlx_new_window(), mlx_loop() 메뉴얼 참고 */
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "hello world");
	mlx_loop(mlx_ptr);
	
}
