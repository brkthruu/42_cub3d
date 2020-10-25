#include "../mlx/mlx.h"
#include <math.h>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

typedef	struct s_info
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;

	double		time;
	double		oldTime;

	void		*mlx;
	void		*win;
	double		moveSpeed;
	double		rotSpeed;
}				t_info;

int	worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	param_init(t_info *info)
{
	info->posX = 22;			//start position
	info->posY = 12;
	info->dirX = -1;			//initial direction vector of player
	info->dirY = 0;
	info->planeX = 0;			//the 2D raycaster version of camera plane
	info->planeY = 0.66;

	info->time = 0;
	info->oldTime = 0;

	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
}
void	calc(t_info *info)
{
	int		x;

	x = 0;
	while (x < screenWidth)
	{
		//calculate ray position and direction
		double	cameraX = 2 * x / (double)screenWidth - 1;
		double	rayDirX = info->dirX + info->planeX * cameraX;		//direction vector of ray
		double	rayDirY = info->dirY + info->planeY * cameraX;

		//which box of the map we're in
		int		mapX = (int)info->posX;
		int		mapY = (int)info->posY;

		//length of ray from current position to next x or y-side
		double	sideDistX;
		double	sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int		stepX;
		int		stepY;

		int		hit = 0;	//was there a wall hit?
		int		side; 		//was a NS or EW wall hit?
		
		x++;
	}
	
}

int		main_loop(t_info *info)
{
	//calculate ray position and direction
	calc(info);

}

int		main(int argc, char *argv[])
{
	t_info	info;

	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, screenWidth, screenHeight, "lodev_Raycaster");
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_loop(info.mlx);
}
