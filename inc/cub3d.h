/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:47 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/11 16:30:01 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include "libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../mlx/mlx.h"

/*pi*/
# define PI 3.1415926535

/*screen*/
# define WIDTH 1280
# define HEIGHT 720
# define FOV 0.66

/*map*/
# define MAP_WIDTH 6
# define MAP_HEIGHT 5
# define TILE_SIZE 1

/*speed*/
# define SPEED 0.1
# define ROT_SPEED 0.05

/*key*/
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define SPACE 32

/*MOUSE KEY*/
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
} t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	orientation;
} t_player;

typedef struct s_door
{
	int		x;
	int		y;
	bool	open;
} t_door;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
	t_door		door;
	int			num_door;
} t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		*map;  // Pointeur vers la map parsée
} t_game;

/*PARS UTILS*/
char	**read_files(char *path);
bool	is_texture(const char *line);
bool	is_color(const char *line);
bool	is_map(const char *line);

/*PARSE_TEXTURE*/
bool	parse_texture(char *line, t_map *map);

/*PARSE_COLORS*/
bool	parse_color(char *line, t_map *map);

/*PARSE_MAP*/
bool	is_valid_map(t_map *map);
int		parse_map(char **lines, t_map *map);

/*PRINCIPAL PARSE*/
int		parse_file(char *filename, t_map *map);

/*KEY*/
int		close_win(t_game *game);
void	rotate(t_game *g, double angle);
int		handle_key(int key, t_game *g);

/*INIT*/
void	init_color(t_color *color);
void	init_texture(t_texture *texture);
void	init_player(t_player *player);
void	init_map(t_map *map);

/*FREE*/
void	free_texture(t_texture *texture);
void	free_map(t_map *map);
void	free_all(t_map *map);

#endif