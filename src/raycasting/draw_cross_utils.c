/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cross_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:30:00 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 15:03:42 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_center_dot(t_game *g, int center_x, int center_y)
{
	put_pixel_to_img(g, center_x, center_y, 0xFF0000);
	put_pixel_to_img(g, center_x - 1, center_y, 0xFF0000);
	put_pixel_to_img(g, center_x + 1, center_y, 0xFF0000);
	put_pixel_to_img(g, center_x, center_y - 1, 0xFF0000);
	put_pixel_to_img(g, center_x, center_y + 1, 0xFF0000);
}

int	calculate_gap(t_game *g)
{
	int	base_gap;

	base_gap = 8;
	if (g->gun.fire_timer > 0)
		return (base_gap + 5);
	return (base_gap);
}

void	draw_horizontal_lines(t_game *g, t_cross_params params)
{
	int	line_length;
	int	thickness;
	int	i;
	int	coords[4];

	line_length = 15;
	thickness = 2;
	i = -thickness / 2;
	while (i <= thickness / 2)
	{
		coords[0] = params.center_x - params.gap - line_length;
		coords[1] = params.center_y + i;
		coords[2] = params.center_x - params.gap;
		coords[3] = params.center_y + i;
		draw_crosshair_line(g, coords);
		coords[0] = params.center_x + params.gap;
		coords[1] = params.center_y + i;
		coords[2] = params.center_x + params.gap + line_length;
		coords[3] = params.center_y + i;
		draw_crosshair_line(g, coords);
		i++;
	}
}
