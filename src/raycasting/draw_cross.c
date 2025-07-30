/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:13 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 14:26:19 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_line_data(t_line *line, int coords[4])
{
	line->dx = coords[2] - coords[0];
	line->dy = coords[3] - coords[1];
	if (abs(line->dx) > abs(line->dy))
		line->steps = abs(line->dx);
	else
		line->steps = abs(line->dy);
	line->x_inc = (float)line->dx / line->steps;
	line->y_inc = (float)line->dy / line->steps;
}

void	draw_crosshair_line(t_game *g, int coords[4])
{
	t_line	line;
	float	x;
	float	y;
	int		i;

	init_line_data(&line, coords);
	x = coords[0];
	y = coords[1];
	i = 0;
	while (i <= line.steps)
	{
		put_pixel_to_img(g, (int)x, (int)y, 0xFF0000);
		x += line.x_inc;
		y += line.y_inc;
		i++;
	}
}

void	draw_crosshair(t_game *g)
{
	int	center_x;
	int	center_y;
	int	size;
	int	coords[4];

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2 + 100;
	size = 15;
	coords[0] = center_x - size;
	coords[1] = center_y;
	coords[2] = center_x + size;
	coords[3] = center_y;
	draw_crosshair_line(g, coords);
	coords[0] = center_x;
	coords[1] = center_y - size;
	coords[2] = center_x;
	coords[3] = center_y + size;
	draw_crosshair_line(g, coords);
}

void	draw_dynamic_crosshair(t_game *g)
{
	t_cross_params	params;

	params.center_x = WIDTH / 2;
	params.center_y = HEIGHT / 2 + 100;
	params.gap = calculate_gap(g);
	draw_center_dot(g, params.center_x, params.center_y);
	draw_horizontal_lines(g, params);
}
