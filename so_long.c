/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:36:04 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/21 14:27:45 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stddef.h>			// NULL
#include <stdlib.h>			// malloc, free
#include <unistd.h>			// close
#include <fcntl.h>  		// open
#include <stdbool.h>
#include "so_long.h"
#include "print_error.h"
#include "ft_string.h"
#include "read_file.h"
#include "ft_split.h"

t_coord2d	coord2d(int x, int y)
{
	t_coord2d	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

void	sl_tx_init(t_texture *tx)
{
	tx->img = NULL;
	tx->height = 0;
	tx->width = 0;
}

void	sl_assets_init(t_game *g)
{
	sl_tx_init(&g->assets[WALL]);
	sl_tx_init(&g->assets[GROUND]);
}

void	sl_map_init(t_game *g)
{
	g->map.grid = NULL;
	g->map.height = 0;
	g->map.width = 0;
	g->map.nbr_collectibles = 0;
	g->map.start = coord2d(-1, -1);
	g->map.exit = coord2d(-1, -1);
}

void	sl_player_init(t_game *g)
{
	g->player.pos = coord2d(-1, -1);
	g->player.moves = 0;
	g->player.state = 0;
	g->player.nbr_collectibles = 0;
}

bool	is_suffix_valid(char *s, char *suffix)
{
	int	i;
	int	len;
	int	suf_len;

	len = ft_strlen(s);
	suf_len = ft_strlen(suffix);
	if (len <= suf_len)
		return (false);
	i = 0;
	while (i < suf_len)
	{
		if (s[len - suf_len + i] != suffix[i])
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_content_valid(char *ascii)
{
	while (*ascii)
	{
		if (*ascii != '\n' && !ft_strrchr(MAP_TILES, *ascii))
			return (false);
		ascii++;
	}
	return (true);
}

int	map_count(char *ascii, char tile)
{
	int count;

	count = 0;
	while (*ascii)
	{
		if (*ascii == tile)
			count++;
		ascii++;
	}
	return (count);
}

int	get_dimensions(char *ascii, int *height, int *width)
{
	int	h;
	int	w;
	int	sublen;

	h = 0;
	w = 0;
	while (ascii[w] != '\n')
		w++;
	while (*ascii)
	{
		h++;
		sublen = substrlen(ascii, '\n');
		if (sublen != w)
			return (1);
		ascii += sublen + 1;
	}
	if (h < 3 || w < 3)
		return (1);
	*height = h;
	*width = w;
	return (0);
}

bool	is_map_enclosed(char *ascii, int height, int width)
{
	int	i;
	int	mod_nl;

	i = 0;
	mod_nl = width + 1;
	while (ascii[i])
	{
		if (i % mod_nl == 0 && ascii[i] != TILE_WALL)
			return (false);
		if (i % mod_nl == width - 1 && ascii[i] != TILE_WALL)
			return (false);
		if (i / mod_nl == 0 || i / mod_nl == height)
		{
			if (i % mod_nl <= width - 1 && ascii[i] != TILE_WALL)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_map_ascii_valid(t_game *g, char *ascii)
{
	int	h;
	int	w;
	int	nbr_c;

	if (!is_map_content_valid(ascii))
		return (print_error(ERR_MAP_BAD_CONTENT), false);
	if (map_count(ascii, TILE_PLAYER) != 1
		|| map_count(ascii, TILE_EXIT) != 1)
		return (print_error(ERR_MAP_TILE_NOT_UNIQUE), false);
	nbr_c = map_count(ascii, TILE_COLLECTIBLE);
	if (nbr_c == 0)
		return (print_error(ERR_MAP_NO_COLLECTIBLES), false);
	if (get_dimensions(ascii, &h, &w))
		return (print_error(ERR_MAP_IS_NOT_RECT), false);
	if (!is_map_enclosed(ascii, h, w))
		return (print_error(ERR_MAP_NOT_ENCLOSED), false);
	if (h * TEX_SIZE >= WIN_MAX_HEIGHT || w * TEX_SIZE >= WIN_MAX_WIDTH)
		return (print_error(ERR_MAP_TOO_BIG), false);
	g->map.height = h;
	g->map.width = w;
	g->map.nbr_collectibles = nbr_c;
	return (true);
}

int	sl_map_load(t_game *g, char *map_file)
{
	int		fd;
	char	*ascii;

	if (!is_suffix_valid(map_file, ".ber"))
		return (print_error(ERR_MAP_FILE_EXT), 1);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_MAP_OPEN_FILE), 1);
	ascii = read_file(fd);
	close(fd);
	if (!ascii)
		return (1);
	if (!is_map_ascii_valid(g, ascii))
		return (free(ascii), 1);
	g->map.grid = ft_split(ascii, '\n');
	free(ascii);
	if (!g->map.grid)
		return (1);
	return (0);
}

void sl_map_clear(t_game *g)
{
	freestrs(g->map.grid, g->map.height);
}

void sl_assets_clear(t_game *g)
{
	int	i;

	if (!g->mlx)
		return ;
	i = 0;
	while (i < TEX_NBR)
	{
		if (g->assets[i].img)
		{
			mlx_destroy_image(g->mlx, g->assets[i].img);
			g->assets[i].img = NULL;
		}
		i++;
	}
}

void	sl_game_exit(t_game *g, char *error_msg)
{
	if (g->mlx_win)
		mlx_destroy_window(g->mlx, g->mlx_win);
	sl_assets_clear(g);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
	sl_map_clear(g);
	if (error_msg)
	{
		print_error(error_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	sl_tx_load(t_game *g, t_texture *tx, char *tx_path)
{
	tx->img = mlx_xpm_file_to_image(g->mlx, tx_path, &tx->width, &tx->height);
	if (tx->height != TEX_SIZE || tx->width != TEX_SIZE)
		sl_game_exit(g, ERR_TXS_SIZE_NOT_CORRECT);
}

int	sl_assets_load(t_game *g)
{
	int	i;

	sl_tx_load(g, &g->assets[NO_TEX], TEX_GROUND);
	sl_tx_load(g, &g->assets[GROUND], TEX_GROUND);
	sl_tx_load(g, &g->assets[PLAYER], TEX_PLAYER);
	sl_tx_load(g, &g->assets[EXIT], TEX_EXIT);
	sl_tx_load(g, &g->assets[WALL], TEX_WALL);
	sl_tx_load(g, &g->assets[COLLECTIBLE], TEX_COLLECTIBLE);
	i = 0;
	while (i < TEX_NBR)
	{
		if (!g->assets[i].img)
			return (1);
		i++;
	}
	return (0);
}

void	sl_game_init(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		sl_game_exit(g, ERR_MLX_INIT_FAILED);
	sl_assets_init(g);
	sl_map_init(g);
	sl_player_init(g);
	g->mlx_win = NULL;
}

int	close_window(void)
{
	printf("CLOSE");
	//sl_game_exit(g, NULL);
	return (0);
}

void	init_mlx_window(t_game *g)
{
	int	win_h;
	int	win_w;

	win_h = g->map.height * TEX_SIZE;
	win_w = g->map.width * TEX_SIZE;
	if (win_h >= WIN_MAX_HEIGHT || win_w >= WIN_MAX_WIDTH)
		sl_game_exit(g, ERR_MAP_TOO_BIG);
	g->mlx_win = mlx_new_window(g->mlx, win_w, win_h, WIN_TITLE);
	if (!g->mlx_win)
		sl_game_exit(g, "Window initialisation failed");
}

void	sl_tile_render(t_game *g, void *img, int pos_x, int pos_y)
{
	int	x;
	int	y;

	x = pos_x * TEX_SIZE;
	y = pos_y * TEX_SIZE;
	mlx_put_image_to_window(g->mlx, g->mlx_win, img, x, y);
}

/*
int	render_tile(t_game *g, t_coord2d)
{
	int	tile_id;

	tile_id = 0;
	while (MAP_TILES[tile_id])
	{
		if (MAP_TILES[tile_id] == tile)
			return (tile_id + 1);
		tile_id++;
	}
	return (0);
}
*/

int	get_tile_index(char tile)
{
	int	tile_id;

	tile_id = 0;
	while (MAP_TILES[tile_id])
	{
		if (MAP_TILES[tile_id] == tile)
			return (tile_id + 1);
		tile_id++;
	}
	return (0);
}

void	sl_game_render(t_game *g)
{
	int		i;
	int		j;
	char	tile;

	init_mlx_window(g);
	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			tile = g->map.grid[i][j];
			sl_tile_render(g, g->assets[get_tile_index(tile)].img, j, i);
			j++;
		}
		i++;
	}
}

t_coord2d	map_find(char **grid, char tile)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == tile)
				return (coord2d(x, y));
			x++;
		}
		y++;
	}
	return (coord2d(-1, -1));
}

void	move(t_game *g, t_coord2d next)
{
	t_coord2d	play;
	t_coord2d	dest;
	char		tile;

	play = g->player.pos;
	dest = coord2d(play.x + next.x, play.y + next.y);
	if (g->map.grid[dest.y][dest.x] == TILE_WALL)
		return ;
	if (g->map.grid[dest.y][dest.x] == TILE_COLLECTIBLE)
		g->player.nbr_collectibles++;
	if (g->map.grid[dest.y][dest.x] == TILE_EXIT
		&& g->player.nbr_collectibles == g->map.nbr_collectibles)
		sl_game_exit(g, NULL);
	tile = g->map.grid[play.y][play.x];
	sl_tile_render(g, g->assets[get_tile_index(tile)].img, play.x, play.y);
	sl_tile_render(g, g->assets[PLAYER].img, dest.x, dest.y);
	g->player.pos = dest;
	g->player.moves++;

}

#include <X11/keysym.h>

int	key_hook(int keycode, t_game *g)
{
	(void)keycode;
	mlx_destroy_window(g->mlx, g->mlx_win);
	return (0);
}

/*
int	key_hook(int keysym, t_game *g)
{
	printf("KEY = %i\n", keysym);
	if (keysym == KEY_LEFT || keysym == 'a')
		move(g, coord2d(-1, 0));
	if (keysym == KEY_UP || keysym == 'w')
		move(g, coord2d(0, -1));
	if (keysym == KEY_RIGHT || keysym == 'd')
		move(g, coord2d(1, 0));
	if (keysym == KEY_DOWN || keysym == 's')
		move(g, coord2d(0, 1));
	return (0);
}
*/

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("File not provided"), 1);
	sl_game_init(&game);
	if (sl_map_load(&game, argv[1]))
		sl_game_exit(&game, NULL);
	if (sl_assets_load(&game))
		sl_game_exit(&game, ERR_TXS_NOT_LOADED);
	game.player.pos = map_find(game.map.grid, TILE_PLAYER);
	sl_game_render(&game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
	//mlx_hook(game.mlx_win, 2, 0, key_hook, &game);
	mlx_loop(game.mlx);
	sl_game_exit(&game, NULL);
	return (0);
}

// TODO : check si toutes les textures ont bien la taille 64x64
// ajouter test finissable
