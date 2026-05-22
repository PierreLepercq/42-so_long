/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:09:52 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/22 01:28:34 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>

# define PASS	0
# define FAIL 	1

/*	ERRORS	*/
# define ERR_MEM_ALLOC				"Memory allocation failed"
# define ERR_OPEN_FILE 				"Unable to open file"
# define ERR_FILE_NOT_PROVIDED 		"File not provided"
# define ERR_MAP_FILE_EXT 			"File extension must be '.ber'"
# define ERR_MAP_NOT_RECT 			"Map is not rectangular"
# define ERR_MAP_BAD_CONTENT 		"Map content is not valid"
# define ERR_MAP_NOT_ENCLOSED 		"Map is not enclosed"
# define ERR_PLAYER_NOT_UNIQUE 		"Zero or more than one player tile exist"
# define ERR_EXIT_NOT_UNIQUE 		"Zero or more than one exit tile exist"
# define ERR_MAP_ELEM_NOT_REACHABLE	"Map elements are not reachable"
# define ERR_NO_COLLECTIBLES		"Map do not have any collectibles"
# define ERR_TXS_NOT_LOADED			"Textures load failed"
# define ERR_TXS_SIZE_NOT_CORRECT	"Textures size are not 64x64 pixels"
# define ERR_MLX_INIT_FAILED		"MLX initialisation failed"
# define ERR_MAP_TOO_BIG			"Map size is too big"

/*	MAP		*/
# define MAP_TILES			"0PE1C"
# define TILE_EMPTY			'0'
# define TILE_PLAYER		'P'
# define TILE_EXIT			'E'
# define TILE_WALL			'1'
# define TILE_COLLECTIBLE	'C'
# define TILE_VISITED		'V'

/* TEXTURES	*/
enum {
	NO_TEX = 0,
	GROUND = 1,
	PLAYER = 2,
	EXIT = 3,
	WALL = 4,
	COLLECTIBLE = 5
};
# define TEX_NBR		6
# define TEX_SIZE		64

# define WIN_TITLE		"Soooo Looooooooooong"
# define WIN_MAX_HEIGHT	1080
# define WIN_MAX_WIDTH	1920

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/*	TEXTURES - PATH */
# define TEX_NO_TEX			"./textures/no_texture.xpm"
# define TEX_GROUND			"./textures/ground.xpm"
# define TEX_PLAYER			"./textures/player.xpm"
# define TEX_EXIT			"./textures/exit.xpm"
# define TEX_WALL			"./textures/wall.xpm"
# define TEX_COLLECTIBLE	"./textures/collectible.xpm"

# define KEY_LEFT			65361
# define KEY_UP				65362
# define KEY_RIGHT			65363
# define KEY_DOWN			65364
# define K_ESC				65307

typedef struct s_coord2d
{
	int			x;
	int			y;
}				t_coord2d;

typedef struct s_player
{
	t_coord2d	pos;
	int			moves;
	int			state;
	int			nbr_collectibles;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			height;
	int			width;
	int			nbr_collectibles;
	t_coord2d	start;
	t_coord2d	exit;
}				t_map;

typedef struct s_texture
{
	void		*img;
	int			height;
	int			width;
}				t_texture;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_texture	assets[TEX_NBR];
	t_map		map;
	t_player	player;
}				t_game;

//	PRINT ERROR
void		print_error(const char *err_msg);

//	COORD2D
t_coord2d	coord2d(int x, int y);

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
void		map_clean(t_map *map);

//	PLAYER
void    	player_init(t_player *player);

#endif