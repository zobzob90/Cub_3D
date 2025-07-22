/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:47 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 16:40:46 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define SPEED 0.05
# define ROT_SPEED 0.05
# define PLAYER_MARGIN 0.2
# define SPRINT_MULTIPLIER 2.0

/*minimap*/
# define MINIMAP_SIZE 150
# define MINIMAP_CELL 8

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
# define CTRL_G 65507
# define CTRL_D 65508
# define ALT_L 65513
# define ALT_R 65514
# define E 101
# define SHIFT_L 65505
# define M 109

/*raycasting optimizations*/
# define FOV 0.66
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/*MOUSE KEY*/
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3
# define MOUSE_SENSITIVITY 0.007

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	orientation;
}	t_player;

typedef struct s_door
{
	int		x;
	int		y;
	bool	open;
}	t_door;

typedef struct s_npc
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	int		hp;
	int		type;
	bool	see_player;
} 	t_npc;

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
	t_door		*doors;
	int			num_doors;
	t_npc		*npcs;
	int			num_npcs;
}	t_map;

typedef struct s_weapon
{
	void	*img;
	char	*tex_repos;
	char	*tex_fire;
	int		tex_height;
	int		tex_width;
	char	*tex_data;
	int		tex_size_line;
	int		tex_bpp;
	int		tex_endian;
	int		fire_timer;
	int		fire_duration;
}	t_weapon;

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
}	t_ray;

typedef struct s_draw_params
{
	int		x;
	int		start;
	int		end;
	t_ray	*ray;
}	t_draw_params;

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
	bool	lock_mouse;
	bool	shift;
}	t_keys;

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
	int			num_npc;
	t_npc		*npc;
	t_map		*map;
	t_keys		*keys;
	t_weapon	gun;
	bool		show_minimap;
}	t_game;

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
int		check_file_extension(char *filename);
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

/*MOUSE*/
int		handle_mouse_press(int button, int x, int y, t_game *g);
int		handle_mouse_release(int button, int x, int y, t_game *g);
int		handle_mouse_move(int x, int y, t_game *g);
void	capture_mouse(t_game *game);

/*MOVEMENT*/
void	rotate(t_game *g, double angle);
int		update_player_movement(t_game *g);
double	get_movement_speed(t_game *g);

/*FIRE*/
void	gun_fire(t_game *g);
void	update_gun_animation(t_game	*g);

/*INIT*/
void	init_color(t_color *color);
void	init_texture(t_texture *texture);
void	init_player(t_player *player);
void	init_player_from_map(t_player *player);
void	init_map(t_map *map);
void	init_doors_from_map(t_map *map);
void	init_npc(t_npc *npc);
void	init_npcs_from_map(t_map *map);
void	set_player_direction(t_player *player);

/*EVENT*/
void	cleanup_game(t_game *game);

/*COLLISION*/
bool	is_valid_position(t_game *game, double x, double y);
bool	can_move_to(t_game *game, double new_x, double new_y);
void	move_player_safe(t_game *game, double delta_x, double delta_y);
bool	check_wall_collision(t_game *game, double x, double y, double margin);

/*DOOR MANAGEMENT*/
void	handle_door_interaction(t_game *game);
bool	is_door(t_game *game, int x, int y);
void	toggle_door(t_game *game, int x, int y);
t_door	*find_door(t_game *game, int x, int y);

/*NPC*/
void	init_npcs_from_map(t_map *map);

/*RAYCASTING*/
void	load_textures(t_game *g);
void	draw_scene(t_game *g);
void	draw_textured_line(t_game *game, t_draw_params *params);
int		get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y);
void	perform_dda(t_game *g, t_ray *r);
void	draw_gun(t_game *g);
void	put_pixel_to_img(t_game *game, int x, int y, int color);

/*MINIMAP*/
void	draw_mini_map(t_game *game);

/*FREE*/
void	free_texture(t_texture *texture);
void	free_map(t_map *map);

#endif