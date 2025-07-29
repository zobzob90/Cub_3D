/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:14:10 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 13:20:06 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_minimap_cell(t_game *game, int px, int py, unsigned int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < MINIMAP_CELL)
	{
		x = 0;
		while (x < MINIMAP_CELL)
		{
			put_pixel_to_img(game, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_minimap_grid(t_game *game)
{
	int				i;
	int				j;
	int				px;
	int				py;
	unsigned int	color;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			px = 10 + j * MINIMAP_CELL;
			py = 10 + i * MINIMAP_CELL;
			color = get_minimap_color(game->map->grid[i][j]);
			draw_minimap_cell(game, px, py, color);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_game *game)
{
	draw_minimap_grid(game);
	render_player(game);
	draw_npc(game);
}
