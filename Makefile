# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 18:25:26 by plepercq          #+#    #+#              #
#    Updated: 2026/05/22 17:01:08 by plepercq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= so_long
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g

MLX			= mlx
MLX_LIB		= lib$(MLX)
MLX_REPO	= https://github.com/42paris/minilibx-linux.git

INC 		= -I include
INC			+= -I $(MLX_LIB)

LINKS		= -L$(MLX_LIB) -l$(MLX) -lXext -lX11 -lm -lz

CFILES		= 	so_long.c			\
				print_error.c		\
				coord2d.c			\
				ft_split.c			\
				ft_string.c			\
				read_file.c			\
				map.c				\
				map_checks.c		\
				map_find.c			\
				map_utils.c			\
				player.c			\
				textures.c			\
				mlx_window.c		\

#				src/coord.c						\
#				src/map_checks.c				\
#				src/map_load.c					\

OBJECTS		= $(CFILES:.c=.o)

IMAGES		=	textures/collectible.png		\
				textures/exit.png				\
				textures/ground.png				\
				textures/no_texture.png			\
				textures/player.png				\
				textures/wall.png				\

TEXTURES	=	$(IMAGES:.png=.xpm)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJECTS) $(TEXTURES)
	@echo ""
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(CFILES) $(LINKS)
	@echo "\n-> $(NAME) : OK"

$(MLX_LIB):
	git clone $(MLX_REPO) $(MLX_LIB)
	$(MAKE) -C $(MLX_LIB);

clean:
	@rm -vf $(OBJECTS)
	$(MAKE) -C $(MLX_LIB) clean

fclean:
	@rm -vf $(NAME) $(OBJECTS)
	@rm -rvf $(MLX_LIB)

re: fclean all

good: re clean

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

%.xpm: %.png
	convert $^ $@

.PHONY: all clean fclean re
