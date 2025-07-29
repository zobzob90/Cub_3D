/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:32:33 by vdeliere          #+#    #+#             */
/*   Updated: 2025/07/24 17:37:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*Put a pixel(x,y) of the gun in the main image*/
static void	put_gun_pixel(t_game *g, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = g->img_data + (y * g->size_line + x * (g->bpp / 8));
	*(unsigned int *)pixel = color;
}

/*Get the color of a pixel from specific texture data*/
static unsigned int	get_gun_pixel_from_data(char *tex_data, int gun_x,
	int gun_y, t_game *g)
{
	char	*pixel;

	if (!tex_data || gun_x < 0 || gun_x >= g->gun.tex_width
		|| gun_y < 0 || gun_y >= g->gun.tex_height)
		return (0xFF00FF);
	pixel = tex_data + (gun_y * g->gun.tex_size_line
			+ gun_x * (g->gun.tex_bpp / 8));
	return (*(unsigned int *)pixel);
}

/*Draw the gun pixel by pixel, ignoring the #00A2E8 color*/
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
		screen_x = (WIDTH - g->gun.tex_width) / 2 + 150;
		gun_x = -1;
		while (++gun_x < g->gun.tex_width)
		{
			color = get_gun_pixel_from_data(g->gun.tex_data, gun_x, gun_y, g);
			if (color != 0x00A2E8 && (color & 0xFFFFFF) != 0)
				put_gun_pixel(g, screen_x, screen_y, color);
			screen_x++;
		}
		screen_y++;
	}
}

static void	draw_crosshair_line(t_game *g, int start_x, int start_y,
							int end_x, int end_y)
{
	int	dx;
	int	dy;
	int	steps;
	int	i;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = end_x - start_x;
	dy = end_y - start_y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = (float)dx / steps;
	y_inc = (float)dy / steps;
	x = start_x;
	y = start_y;
	i = 0;
	while (i <= steps)
	{
		put_gun_pixel(g, (int)x, (int)y, 0xFF0000);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	draw_crosshair(t_game *g)
{
	int	center_x;
	int	center_y;
	int	size;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2 + 100;
	size = 15;
	draw_crosshair_line(g, center_x - size, center_y, center_x + size, center_y);
	draw_crosshair_line(g, center_x, center_y - size, center_x, center_y + size);
}

void	draw_advanced_crosshair(t_game *g)
{
	int	center_x;
	int	center_y;
	int	outer_size;
	int	inner_size;
	int	thickness;
	int	i;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2 + 100;
	outer_size = 20;
	inner_size = 5;
	thickness = 2;
	i = -thickness;
	while (i <= thickness)
	{
		draw_crosshair_line(g, center_x - outer_size, center_y + i, 
			center_x - inner_size, center_y + i);
		draw_crosshair_line(g, center_x + inner_size, center_y + i,
			center_x + outer_size, center_y + i);
		draw_crosshair_line(g, center_x + i, center_y - outer_size,
			center_x + i, center_y - inner_size);
		draw_crosshair_line(g, center_x + i, center_y + inner_size,
			center_x + i, center_y + outer_size);
		i++;
	}
}
