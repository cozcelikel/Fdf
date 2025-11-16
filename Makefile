# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cozcelik <cozcelik@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 14:56:46 by cozcelik          #+#    #+#              #
#    Updated: 2025/11/16 00:25:56 by cozcelik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRC = main.c \
	  read_map.c \
	  split.c \
	  get_next_line.c \
	  get_next_line_utils.c \
	  read_map_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C minilibx-linux
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iminilibx-linux -c $< -o $@

clean:
	make -C minilibx-linux clean
	rm -f $(OBJ)

fclean: clean
	make -C minilibx-linux clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
