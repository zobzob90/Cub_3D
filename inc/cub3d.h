/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:47 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/04 11:07:00 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include "libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <minilibx-linux/mlx.h>

/*screen*/
# define WIDTH 800
# define HEIGHT 800

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
	char	orientation;
} t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
	t_player	player;
} t_map;


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