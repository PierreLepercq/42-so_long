# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/07 18:25:26 by plepercq          #+#    #+#              #
#    Updated: 2026/05/26 03:43:49 by plepercq         ###   ########.fr        #
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

CFILES		= 	so_long.c						\
				src/coord2d.c					\
				src/ft_split.c					\
				src/ft_string.c					\
				src/map_checks.c				\
				src/map_find.c					\
				src/map_utils.c					\
				src/map.c						\
				src/mlx_window.c				\
				src/player.c					\
				src/print_utils.c				\
				src/print_error.c				\
				src/read_file.c					\
				src/textures.c					\

OBJECTS		= $(CFILES:.c=.o)

IMAGES		=	textures/collectible.png		\
				textures/exit.png				\
				textures/ground.png				\
				textures/no_texture.png			\
				textures/player.png				\
				textures/wall.png				\
				textures/exit_open.png			\
				textures/exit_win.png			\

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

fclean:
	@rm -vf $(NAME) $(OBJECTS)
	@rm -rvf $(MLX_LIB)

re: fclean all

good: re clean

test: re
	@echo -e "\nTests :";
	./$(NAME);
	./$(NAME) unknown.ber;
	./$(NAME) ./maps/tmap_wrong_extension.test;
	./$(NAME) ./maps/tmap_bad_content.ber;
	./$(NAME) ./maps/tmap_multiple_E.ber;
	./$(NAME) ./maps/tmap_multiple_P.ber;
	./$(NAME) ./maps/tmap_with_nl.ber;
	./$(NAME) ./maps/tmap_not_rectangular.ber;
	./$(NAME) ./maps/tmap_not_enclosed.ber;
	./$(NAME) ./maps/tmap_not_playable.ber;

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $^ -o $@

%.xpm: %.png
	convert $^ $@

.PHONY: all clean fclean re
