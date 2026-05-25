/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:09:52 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/25 21:37:18 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stddef.h>
# include <stdbool.h>
# include "coord2d.h"

//	CUSTOM
# define PASS	0
# define FAIL 	1

//	MLX WINDOW
# define WIN_TITLE			"So Long"
# define WIN_MAX_HEIGHT		1080
# define WIN_MAX_WIDTH		1920

# define KEY_LEFT			65361
# define KEY_UP				65362
# define KEY_RIGHT			65363
# define KEY_DOWN			65364
# define K_ESC				65307

//	MAP
# define MAP_TILES			"01CEP"

# define TILE_GROUND		'0'
# define TILE_WALL			'1'
# define TILE_COLLECTIBLE	'C'
# define TILE_EXIT			'E'
# define TILE_PLAYER		'P'
# define TILE_VISITED		'V'

//	TEXTURES
# define NO_TEX				0
# define GROUND				1
# define WALL				2
# define COLLECTIBLE		3
# define EXIT				4
# define PLAYER				5
# define WIN				6

# define TEX_NBR			7
# define TEX_SIZE			64

# define TEX_NO_TEX			"./textures/no_texture.xpm"
# define TEX_GROUND			"./textures/ground.xpm"
# define TEX_WALL			"./textures/wall.xpm"
# define TEX_COLLECTIBLE	"./textures/collectible.xpm"
# define TEX_EXIT			"./textures/exit.xpm"
# define TEX_PLAYER			"./textures/player.xpm"
# define TEX_WIN			"./textures/win.xpm"

//	ERRORS
# define ERR_FILE_NOT_PROVIDED 		"File not provided"
# define ERR_MAP_FILE_EXT 			"File extension must be '.ber'"
# define ERR_MAP_NOT_RECT 			"Map is not rectangular"
# define ERR_MAP_BAD_CONTENT 		"Map content is not valid"
# define ERR_MAP_NOT_ENCLOSED 		"Map is not enclosed"
# define ERR_PLAYER_NOT_UNIQUE 		"Zero or more than one player tile exist"
# define ERR_EXIT_NOT_UNIQUE 		"Zero or more than one exit tile exist"
# define ERR_MAP_ELEM_NOT_REACHABLE	"Map elements are not reachable"
# define ERR_NO_COLLECTIBLES		"Map do not have any collectibles"
# define ERR_TX_NOT_LOADED			"Texture load failed"
# define ERR_TX_SIZE_NOT_CORRECT	"Texture size is not 64x64 pixels"
# define ERR_MLX_INIT_FAILED		"MLX initialisation failed"
# define ERR_MLX_WIN_INIT_FAILED	"MLX Window initialisation failed"
# define ERR_MAP_TOO_BIG			"Map size is too big"
# define ERR_MAP_IS_NOT_PLAYABLE	"Map is not playable"

typedef struct s_map
{
	char		**grid;
	int			height;
	int			width;
	int			nbr_collectibles;
	t_coord2d	start;
	t_coord2d	exit;
}				t_map;

typedef struct s_player
{
	t_coord2d	pos;
	int			moves;
	int			state;
	int			nbr_collectibles;
}				t_player;

typedef struct s_texture
{
	void		*img;
	int			height;
	int			width;
}				t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_texture	txs[TEX_NBR];
	t_map		map;
	t_player	player;
	int			win;
}				t_game;

//	PRINT UTILS
void		writenbr(int n, int fd);
void		ft_putnbr_fd(int n, int fd);
void		print_moves(int nbr_moves);
void		print_win(t_game *game);

//	MAP UTILS
int			char_count(char *str, char c);
int			get_dimensions(char *ascii, int *height, int *width);
int			map_count(char **grid, char tile);
t_coord2d	map_find(char **grid, char tile);

//	MAP FIND
char		**gridcpy(char **strs);
bool		flood_fill(char **grid, t_coord2d pos, t_coord2d target);
bool		is_reachable(char **grid, t_coord2d start, t_coord2d target);

//	MAP CHECKS
bool		is_suffix_valid(char *s, char *suffix);
bool		is_map_content_valid(char *ascii);
bool		is_map_enclosed(char *ascii, int height, int width);
bool		is_map_playable(char *ascii, int height);
bool		is_map_valid(char *ascii);

//	MAP
void		map_init(t_map *map);
int			map_build(t_map *map, char *ascii);
int			map_load(t_map *map, char *map_file);
void		map_clear(t_map *map);
void		map_draw(t_game *g);

//	PLAYER
void		player_init(t_player *player);
int			player_move(t_game *g, t_coord2d dest);

//	TEXTURES
void		tx_init(t_texture *tx);
void		textures_init(t_texture *txs);
void		tx_load(t_game *g, t_texture *tx, char *tx_path);
void		textures_load(t_game *g);
void		textures_clear(t_game *game);

//	MLX WINDOW
int			get_tile_index(char tile);
void		tile_render(t_game *g, void *img, int pos_x, int pos_y);
void		move(t_game *g, t_coord2d next);
int			key_hook(int keysym, void *game);
void		mlx_window_init(t_game *game);

//	MAIN : SO LONG
int			game_exit(t_game *game, char *err_msg);
int			game_init(t_game *game, char *map_file);
int			game_launch(t_game *game);

#endif