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

	ceiling_color = (game->map->ceiling.r << 16)
		| (game->map->ceiling.g << 8) | game->map->ceiling.b;
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

	floor_color = (game->map->floor.r << 16)
		| (game->map->floor.g << 8) | game->map->floor.b;
	y = end;
	while (y < HEIGHT)
	{
		put_pixel_to_img(game, x, y, floor_color);
		y++;
	}
}

static void	draw_wall_texture(t_game *game, t_draw_params *params)
{
	int		y;
	int		tex_num;
	int		tex_y;
	double	step;
	double	tex_pos;

	tex_num = get_texture_num(params->ray);
	step = 1.0 * TEX_HEIGHT / (int)(HEIGHT / params->ray->perp_wall_dist);
	tex_pos = (params->start - (-(int)(HEIGHT
					/ params->ray->perp_wall_dist) / 2 + HEIGHT / 2)) * step;
	y = params->start;
	while (y < params->end)
	{
		tex_y = (int)tex_pos % TEX_HEIGHT;
		if (tex_y < 0)
			tex_y = 0;
		tex_pos += step;
		put_pixel_to_img(game, params->x, y,
			get_texture_pixel(game, tex_num, params->ray->tex_x, tex_y));
		y++;
	}
}

void	draw_textured_line(t_game *game, t_draw_params *params)
{
	draw_ceiling(game, params->x, params->start);
	draw_wall_texture(game, params);
	draw_floor(game, params->x, params->end);
}
