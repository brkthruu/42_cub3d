/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:53:41 by hjung             #+#    #+#             */
/*   Updated: 2020/11/08 17:17:29 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "./Libft/libft.h"
# include "./parse_cub/get_next_line.h"
# include "./mlx/mlx.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define TILE_SIZE 32
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE

# define IMG_WIDTH 400
# define IMG_HEIGHT 300


typedef struct		s_img
{
	int				img_width;
	int 			img_height;
	//아래 3개 값은 이해 안해도 사용하는데 지장이 없음. 
	//선언한뒤 함수의 인자로만 잘 넣어주면 알아서 정보를 받아나옴.
	int				size_l;
	int				bpp;
	int				endian;
	void			*img_ptr;
	int				*data;
}					t_img;

typedef struct		s_ray
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			s_dist_x;
	double			s_dist_y;
	double			d_dist_x;
	double			d_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef	struct		s_cub_info
{
	char			*file_name;
	int				scr_width;
	int				scr_height;
	int				color_floor;
	int				color_ceil;
	int				rows;
	int				cols;
	char			**map;
	t_img			**textures;
}					t_cub_info;

typedef	struct			s_player
{
	double				posx;
	double				posy;
	double				speed;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				rotate_speed;
	double				cam_height;
	int					health;
}						t_player;

typedef struct		s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			*img;
	t_cub_info		*cub_info;
	t_player		*player;
}					t_game;

int		init_game(t_game *game);
int		init_cub_info(t_game *game);
int		init_textures(t_game *game, int nbr_textures);
int 	init_player(t_game *game);
int		init_image(t_game *game);

int		parse_config(t_game *game);
int		parse_color(t_game *game, char *line, char opt);

int		generate_buf_map(t_game *game, char *line, char **buf_map);
int		copy_map_data(t_game *game, char *buf_map);
int		chk_map_validity(t_game *game);

int		game_loop(t_game *game);
void	calc(t_game *game, t_ray *ray);
void	init_ray(t_game *game, t_ray *ray, int x);
void	verLine(t_game *game, int x, int y1, int y2, int color);
void	adjust_texture(t_game *game, t_ray *ray, int x);
void	floor_ceiling(t_game *game);
void	draw(t_game *game);

void	leave(int mod, t_game *game, char *msg);

int		is_whitespace(int c);

#endif
