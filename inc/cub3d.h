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
# define WIDTH 1920
# define HEIGHT 1080

/*player parameters*/
# define SPEED 0.1
# define ROT_SPEED 0.05
# define PLAYER_MARGIN 0.2

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

/*raycasting optimizations*/
# define FOV 0.66
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

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

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	double		wall_x;
	int			tex_x;
	int			tex_y;
} t_ray;

typedef struct s_draw_params
{
	int		x;
	int		start;
	int		end;
	t_ray	*ray;
} t_draw_params;

typedef struct s_keys
{
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
} t_keys;


typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	void		*tex_north;
	void		*tex_south;
	void		*tex_east;
	void		*tex_west;
	char		*tex_north_data;
	char		*tex_south_data;
	char		*tex_east_data;
	char		*tex_west_data;
	int			tex_width;
	int			tex_height;
	int			tex_bpp;
	int			tex_size_line;
	int			tex_endian;
	t_map		*map;
	t_keys		*keys;
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

/*PARSE_GRID*/
int		extract_map_grid(char **lines, int start, t_map *map);

/*PARSE_PLAYER*/
int		find_player(t_map *map);

/*PRINCIPAL PARSE*/
int		parse_file(char *filename, t_map *map);

/*KEY*/
int		close_win(t_game *game);
int		handle_press_key(int key, t_game *g);
int		handle_release_key(int key, t_game *g);

/*Movement*/
void	rotate(t_game *g, double angle);
int	update_player_movement(t_game *g);

/*INIT*/
void	init_color(t_color *color);
void	init_texture(t_texture *texture);
void	init_player(t_player *player);
void	init_player_from_map(t_player *player);
void	init_map(t_map *map);
void	set_player_direction(t_player *player);

/*EVENT*/
void	cleanup_game(t_game *game);

/*COLLISION*/
bool	is_valid_position(t_game *game, double x, double y);
bool	can_move_to(t_game *game, double new_x, double new_y);
void	move_player_safe(t_game *game, double delta_x, double delta_y);
bool	check_wall_collision(t_game *game, double x, double y, double margin);

/*RAYCASTING*/
void	load_textures(t_game *g);
void	draw_scene(t_game *g);
void	draw_textured_line(t_game *game, t_draw_params *params);
int		get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y);
void	perform_dda(t_game *g, t_ray *r);

/*DRAW*/
void	put_pixel_to_img(t_game *game, int x, int y, int color);
void	draw_vertical_line(t_game *game, t_draw_params *params, int color);

/*FREE*/
void	free_texture(t_texture *texture);
void	free_map(t_map *map);

#endif