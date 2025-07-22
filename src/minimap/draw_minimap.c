/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:14:10 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 10:49:28 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_minimap_color(char cell)
{
	if (cell == '1')
		return (0x888888);
	else if (cell == 'D')
		return (0xFFD700);
	else if (cell == 'O')
		return (0xFF8800);
	return (0x222222);
}

static void	render_player(t_game *game)
{
	int	px;
	int	py;
	int	y;
	int	x;

	px = 10 + (int)game->player.x * MINIMAP_CELL;
	py = 10 + (int)game->player.y * MINIMAP_CELL;
	y = -2;
	x = -2;
	while (y <= 2)
	{
		while (x <= 2)
		{
			put_pixel_to_img(game, px + x, py + y, 0x00FF00);
			x++;
		}
		y++;
	}
}

void	draw_mini_map(t_game *game)
{
	int				i;
	int				j;
	int				y;
	int				x;
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
			j++;
		}
		i++;
	}
	render_player(game);
}
