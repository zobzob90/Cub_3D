/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:01:01 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 16:04:48 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
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

typedef struct s_sprite_draw
{
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
	int	sprite_screen_x;
	int	stripe;
	int	y;
}	t_sprite_draw;

typedef struct s_zbuffer_draw
{
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		sprite_screen_x;
	int		stripe;
	int		y;
	double	sprite_distance;
	int		anim_frame;
}	t_zbuffer_draw;

typedef struct s_sprite
{
	void	*img;
	char	*img_data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_sprite;

typedef struct s_npc
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	int		hp;
	int		type;
	bool	see_player;
	int		anim_frame;
	int		anim_timer;
}	t_npc;

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

typedef struct s_line
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
}	t_line;

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
	t_map		*map;
	t_keys		*keys;
	t_weapon	gun;
	int			num_npc;
	t_npc		*npc;
	t_sprite	sprite[3];
	double		z_buffer[WIDTH];
	bool		show_minimap;
}	t_game;

/*PARS UTILS*/
char			**read_files(char *path);
bool			is_texture(const char *line);
bool			is_color(const char *line);
bool			is_map(const char *line);

/*PARSE TEXTURE UTILS*/
int				assign_texture_path_noso(char *direction,
					char *path, t_map *map);
int				assign_texture_path_eawe(char *direction,
					char *path, t_map *map);
int				assign_texture_path(char *direction, char *path, t_map *map);

/*PARSE_TEXTURE*/
bool			parse_texture(char *line, t_map *map);

/*PARSE_COLORS*/
bool			parse_color(char *line, t_map *map);

/*PARSE_MAP*/
bool			is_valid_map(t_map *map);
int				check_file_extension(char *filename);
int				parse_map(char **lines, t_map *map);

/*PARSE_GRID*/
int				extract_map_grid(char **lines, int start, t_map *map);

/*PARSE_PLAYER*/
int				find_player(t_map *map);

/*PRINCIPAL PARSE UTILS*/
int				is_empty_line(char *line);
int				process_config_line(char *line, t_map *map, int *parsed_count);
int				parse_textures_and_colors(char **lines, t_map *map);
int				validate_parsing(t_map *map);

/*PRINCIPAL PARSE*/
int				parse_file(char *filename, t_map *map);

/*KEY*/
int				close_win(t_game *game);
int				handle_press_key(int key, t_game *g);
int				handle_release_key(int key, t_game *g);

/*MOUSE*/
int				handle_mouse_press(int button, int x, int y, t_game *g);
int				handle_mouse_move(int x, int y, t_game *g);
void			capture_mouse(t_game *game);

/*MOVEMENT*/
void			rotate(t_game *g, double angle);
int				update_player_movement(t_game *g);
double			get_movement_speed(t_game *g);

/*FIRE*/
void			gun_fire(t_game *g);
void			update_gun_animation(t_game	*g);

/*INIT*/
void			init_color(t_color *color);
void			init_texture(t_texture *texture);
void			init_player(t_player *player);
void			init_player_from_map(t_player *player);
void			init_map(t_map *map);
void			init_doors_from_map(t_map *map);
void			init_npc(t_npc *npc);
void			init_npcs_from_map(t_map *map);
void			set_player_direction(t_player *player);
void			init_keys(t_game *game);
void			init_gun(t_weapon *gun);
void			init_game(t_game *game);

/*EVENT*/
void			cleanup_game(t_game *game);

/*COLLISION*/
bool			is_valid_position(t_game *game, double x, double y);
bool			can_move_to(t_game *game, double new_x, double new_y);
void			move_player_safe(t_game *game, double delta_x, double delta_y);
bool			check_wall_collision(t_game *game, double x,
					double y, double margin);

/*DOOR MANAGEMENT*/
void			handle_door_interaction(t_game *game);
bool			is_door(t_game *game, int x, int y);
void			toggle_door(t_game *game, int x, int y);
t_door			*find_door(t_game *game, int x, int y);

/*NPC*/
void			load_pig_sprite(t_game *game);
void			update_single_npc(t_game *game, t_npc *npc);
void			update_npc(t_game *game);
void			draw_npcs_sprites(t_game *game);
void			draw_sprite_column(t_game *game, int sprite_screen_x,
					int sprite_height, int sprite_width);
void			draw_sprite_column_with_zbuffer(t_game *game,
					t_zbuffer_draw *draw, int sprite_height, int sprite_width);
void			calculate_sprite_transform(t_game *game,
					t_npc *npc, double *trans_x, double *trans_y);
double			calculate_sprite_distance(t_npc *npc, t_player *player);
void			setup_sprite_draw(t_zbuffer_draw *draw, t_npc *npc,
					int sprite_screen_x, double transform_y);
void			init_sprite_bounds(t_sprite_draw *draw, int sprite_screen_x,
					int sprite_height, int sprite_width);
int				get_pixel_from_sprite(t_sprite *sprite, int x, int y);
int				is_transparent_pixel(int color);
void			init_sprite_bounds(t_sprite_draw *draw,
					int sprite_screen_x, int sprite_height, int sprite_width);
void			init_zbuffer_bounds(t_zbuffer_draw *draw,
					int sprite_screen_x, int sprite_height, int sprite_width);
void			draw_sprite_pixel(t_game *game,
					t_sprite_draw *draw, int sprite_height, int sprite_width);
void			draw_zbuffer_pixel(t_game *game,
					t_zbuffer_draw *draw, int sprite_height, int sprite_width);
void			render_zbuffer_column(t_game *game, t_zbuffer_draw *draw,
					int sprite_height, int tex_x);

/*RAYCASTING*/
void			load_textures(t_game *g);
void			draw_scene(t_game *g);
void			draw_textured_line(t_game *game, t_draw_params *params);
int				get_texture_pixel(t_game *game,
					int tex_num, int tex_x, int tex_y);
void			perform_dda(t_game *g, t_ray *r);
void			draw_gun(t_game *g);
/*CROSSHAIR*/
typedef struct s_cross_params
{
	int	center_x;
	int	center_y;
	int	gap;
}	t_cross_params;

void			draw_crosshair(t_game *g);
void			draw_dynamic_crosshair(t_game *g);
void			draw_crosshair_line(t_game *g, int coords[4]);
void			draw_center_dot(t_game *g, int center_x, int center_y);
int				calculate_gap(t_game *g);
void			draw_horizontal_lines(t_game *g, t_cross_params params);
void			draw_advanced_crosshair(t_game *g);
void			draw_dynamic_crosshair(t_game *g);
void			put_pixel_to_img(t_game *game, int x, int y, int color);

/*MINIMAP*/
void			draw_npc(t_game *game);
void			render_player(t_game *game);
unsigned int	get_minimap_color(char cell);
void			draw_mini_map(t_game *game);

/*FREE*/
void			free_texture(t_texture *texture);
void			free_map(t_map *map);

#endif