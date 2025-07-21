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

static void	put_gun_pixel(t_game *g, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = g->img_data + (y * g->size_line + x * (g->bpp / 8));
	*(unsigned int *)pixel = color;
}

static unsigned int	get_gun_pixel(t_game *g, int gun_x, int gun_y)
{
	char	*pixel;

	if (!g->gun.tex_data || gun_x < 0 || gun_x >= g->gun.tex_width
		|| gun_y < 0 || gun_y >= g->gun.tex_height)
		return (0xFF00FF);
	pixel = g->gun.tex_data + (gun_y * g->gun.tex_size_line
			+ gun_x * (g->gun.tex_bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_gun(t_game *g)
{
	int				screen_x;
	int				screen_y;
	int				gun_x;
	int				gun_y;
	unsigned int	color;

	if (!g->gun.tex_data)
		return ;
	screen_y = HEIGHT - g->gun.tex_height;
	gun_y = -1;
	while (++gun_y < g->gun.tex_height)
	{
		screen_x = (WIDTH - g->gun.tex_width) / 2;
		gun_x = -1;
		while (++gun_x < g->gun.tex_width)
		{
			color = get_gun_pixel(g, gun_x, gun_y);
			if (color != 0x00A2E8 && (color & 0xFFFFFF) != 0)
				put_gun_pixel(g, screen_x, screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}
