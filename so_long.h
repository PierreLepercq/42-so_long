/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plepercq <plepercq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 12:09:52 by plepercq          #+#    #+#             */
/*   Updated: 2026/05/19 16:15:18 by plepercq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*	ERRORS	*/
# define ERR_FILE_NOT_PROVIDED 		"File not provided"
# define ERR_MAP_FILE_EXT 			"File extension must be '.ber'"
# define ERR_MAP_OPEN_FILE 			"Unable to open map file"
# define ERR_MAP_IS_NOT_RECT 		"Map is not rectangular"
# define ERR_MAP_BAD_CONTENT 		"Map content is not valid"
# define ERR_MAP_NOT_ENCLOSED 		"Map is not enclosed"
# define ERR_MAP_TILE_NOT_UNIQUE 	"Number of unique tiles is wrong"
# define ERR_MAP_ELEM_NOT_REACHABLE	"Map elements are not reachable"
# define ERR_MAP_NO_COLLECTIBLES	"Map do not have any collectibles"
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

typedef struct s_vars {
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

#endif