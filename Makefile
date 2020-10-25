# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hjung <hjung@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/22 14:00:47 by hjung             #+#    #+#              #
#    Updated: 2020/10/25 19:06:09 by hjung            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = main.c
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
	rm -f $(NAME)

re : fclean all