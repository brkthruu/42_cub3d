# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hjung <hjung@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/22 14:00:47 by hjung             #+#    #+#              #
#    Updated: 2020/11/11 18:03:38 by hjung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC	=	main.c \
		parse_cub/get_next_line.c \
		parse_cub/parse_config.c \
		parse_cub/parse_color.c \
		parse_cub/parse_map.c\
		parse_cub/chk_map_validity.c\
		parse_cub/parse_sprite.c\
		engine/init_game.c\
		engine/game_loop.c\
		engine/texture.c\
		engine/deal_key.c\
		engine/player_move.c\
		engine/sprite.c\
		utils/sort_sprites.c\
		utils/is_whitespace.c\
		utils/capture_bmp.c
		
OBJ = $(SRC:.c=.o)
LIBFT		= ./Libft/libft.a

all : $(NAME)

%.o: %.c
	$(CC) -Imlx -c $< -o $@
	# $(CC) $(FLAGS) -Imlx -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(LIBFT) -L./mlx -lmlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

$(LIBFT):
	make -C ./Libft
	
clean :
	rm -rf ${OBJ}
	rm -f a.out

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)

re : fclean all