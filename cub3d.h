/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjung <hjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:53:41 by hjung             #+#    #+#             */
/*   Updated: 2020/10/25 19:05:09 by hjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "./Libft/libft.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

# define MAP_WIDTH 15
# define MAP_HEIGHT 11

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			img_width;
	int 		img_height;
	//아래 3개 값은 이해 안해도 사용하는데 지장이 없음. 
	//선언한뒤 함수의 인자로만 잘 넣어주면 알아서 정보를 받아나옴.
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;

	int			map[MAP_HEIGHT][MAP_WIDTH];
}				t_game;


#endif
