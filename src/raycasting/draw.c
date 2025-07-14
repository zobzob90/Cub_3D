/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-09 16:09:32 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-09 16:09:32 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Put a pixel inside the image buffer*/
void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;
	
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = game->img_data + (y * game->size_line + x * (game->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

/*Draw a vertical line in the screen(roof + floor + wall)*/
void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = 0;
	while (y < start)
	{
		put_pixel_to_img(game, x, y, 0x000000);
		y++;
	}
	y = start;
	while (y < end)
	{
		put_pixel_to_img(game, x, y, color);
		y++;
	}
	y = end;
	while (y < HEIGHT)
	{
		put_pixel_to_img(game, x, y, 0x444444);
		y++;
	}
}

static int	get_texture_num(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}

static void	draw_ceiling(t_game *game, int x, int start)
{
	int	y;
	int	ceiling_color;

	// Utiliser la couleur du plafond parsée
	ceiling_color = (game->map->ceiling.r << 16) | (game->map->ceiling.g << 8) | game->map->ceiling.b;
	
	y = 0;
	while (y < start)
	{
		put_pixel_to_img(game, x, y, ceiling_color);
		y++;
	}
}

static void	draw_floor(t_game *game, int x, int end)
{
	int	y;
	int	floor_color;

	// Utiliser la couleur du sol parsée
	floor_color = (game->map->floor.r << 16) | (game->map->floor.g << 8) | game->map->floor.b;
	
	y = end;
	while (y < HEIGHT)
	{
		put_pixel_to_img(game, x, y, floor_color);
		y++;
	}
}

static void	draw_wall_texture(t_game *game, int x, int start, int end, t_ray *ray)
{
	int		y;
	int		tex_num;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;
	int		line_height;
	int		draw_start;
	int		draw_end;

	tex_num = get_texture_num(ray);
	
	// Calculer la vraie hauteur de ligne avant clipping
	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	
	// Calculer les vraies positions de début et fin
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	
	// Calculer le step pour la texture
	step = 1.0 * TEX_HEIGHT / line_height;
	
	// Position de départ de la texture basée sur la position réelle
	tex_pos = (start - draw_start) * step;
	
	y = start;
	while (y < end)
	{
		tex_y = (int)tex_pos % TEX_HEIGHT;
		if (tex_y < 0)
			tex_y = 0;
		
		tex_pos += step;
		
		color = get_texture_pixel(game, tex_num, ray->tex_x, tex_y);
		put_pixel_to_img(game, x, y, color);
		y++;
	}
}

void	draw_textured_line(t_game *game, int x, int start, int end, t_ray *ray)
{
	draw_ceiling(game, x, start);
	draw_wall_texture(game, x, start, end, ray);
	draw_floor(game, x, end);
}
