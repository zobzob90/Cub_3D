/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-17 12:32:33 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-17 12:32:33 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_gun_color(t_game *g, int x, int y)
{
	char			*gun_pixel;

	gun_pixel = g->gun.tex_data + (y * g->gun.tex_size_line + x * (g->gun.tex_bpp / 8));
	return (*(unsigned int *)gun_pixel);
}

void	draw_gun_overlay(t_game *g)
{
	int				gun_x;
	int				gun_y;
	int				x;
	int				y;
	unsigned int	gun_color;
	char			*screen_pixel;

	gun_x = (WIDTH - g->gun.tex_width) / 2;
	gun_y = HEIGHT - g->gun.tex_height;
	x = gun_x;
	y = gun_y;
	while (y < (gun_y + g->gun.tex_height))
	{
		while (x < (gun_x + g->gun.tex_width))
		{
			gun_color = get_gun_color(g, x, y);
			if (gun_color != 0x00A2E8)
			{
				screen_pixel = g->img_data + (y * g->size_line + x * (g->bpp / 8));
				*(unsigned int *)screen_pixel = gun_color;
			}
			x++;
		}
		y++;
	}
}

// void	draw_gun(t_game *g)
// {
// 	int	x;
// 	int	y;

// 	x = (WIDTH - g->gun.tex_width) / 2;
// 	y = HEIGHT - g->gun.tex_height;
// 	mlx_put_image_to_window(g->mlx, g->win, g->gun.img, x, y);
// }