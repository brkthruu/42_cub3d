/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:53:41 by hjung             #+#    #+#             */
/*   Updated: 2020/11/12 21:14:18 by hjung            ###   ########.fr       */
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

# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_LEFT 				123
# define KEY_RIGHT				124

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			distance;
}					t_sprite;

typedef struct		s_draw_sprite
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				u_div;
	int				v_div;
	int				v_move;
	int				v_move_screen;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				y;
	int				d;
	int				tex_x;
	int				tex_y;
	int				color;
	int				totcolor;
}					t_draw_sprite;

typedef struct		s_img
{
	int				img_width;
	int				img_height;
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
	double			*z_buffer;
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

typedef	struct		s_player
{
	double			posx;
	double			posy;
	double			speed;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			rotate_speed;
	double			cam_height;
	int				health;
}					t_player;

typedef struct		s_teximg
{
	int				tex_index;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			tex_pos;
	double			step;
}					t_teximg;

typedef struct		s_game
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				save;
	t_img			*img;
	t_cub_info		*cub_info;
	t_player		*player;
	t_sprite		*sprites;
	int				num_sprite;
	char			*buf_map;
}					t_game;

int					init_game(t_game *game, char *argv);
int					init_cub_info(t_game *game);
int					init_textures(t_game *game, int nbr_textures);
int					init_player(t_game *game);
int					init_image(t_game *game);
int					init_sprite(t_game *game);

int					parse_config(t_game *game, char *argv);
int					parse_color(t_game *game, char *line, char opt);

int					generate_buf_map(t_game *game, char *line);
int					copy_map_data(t_game *game, char *buf_map);
int					chk_map_validity(t_game *game);
int					chk_config_validity(t_game *game, t_cub_info *cub_info);
int					sprite_cnt(t_game *game);

int					game_loop(t_game *game);
void				calc(t_game *game, t_ray *ray);
void				init_ray(t_game *game, t_ray *ray, int x);
void				adjust_texture(t_game *game, t_ray *ray, int x);
void				coloring_floor_ceiling(t_game *game);

int					key_press(int key, t_game *game);
int					key_release(int key, t_game *game);
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);
void				rotate_left(t_game *game);
void				rotate_right(t_game *game);
void				leave(int mod, t_game *game, char *msg);

void				sprite_casting(t_game *game, t_ray *ray);
void				sort_sprites(t_game *game, int num_sprite);

int					is_whitespace(int c);
int					capture_bmp(t_game *game);
int					save_header(t_game *game, int fd, int f_size);
int					save_data(t_game *game, int fd, int pad);
int					get_color(t_game *game, int x, int y);
void				write_4bytes(unsigned char *bytes, int value);

void				free_sprite(t_ray *ray);
#endif
