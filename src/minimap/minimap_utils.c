/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:20:11 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 13:24:57 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

unsigned int	get_minimap_color(char cell)
{
	if (cell == '1')
		return (0x888888);
	else if (cell == 'D')
		return (0xFFD700);
	else if (cell == 'O')
		return (0xFF8800);
	return (0x222222);
}

void	render_player(t_game *game)
{
	int	px;
	int	py;
	int	y;
	int	x;

	px = 10 + (int)game->player.x * MINIMAP_CELL;
	py = 10 + (int)game->player.y * MINIMAP_CELL;
	y = -2;
	while (y <= 2)
	{
		x = -2;
		while (x <= 2)
		{
			put_pixel_to_img(game, px + x, py + y, 0x00FF00);
			x++;
		}
		y++;
	}
}

void	draw_npc(t_game *game)
{
	int	i;
	int	px;
	int	py;
	int	x;
	int	y;

	i = 0;
	while (i < game->map->num_npcs)
	{
		px = 10 + (int)game->map->npcs[i].x * MINIMAP_CELL;
		py = 10 + (int)game->map->npcs[i].y * MINIMAP_CELL;
		y = -1;
		while (y <= 1)
		{
			x = -1;
			while (x <= 1)
			{
				put_pixel_to_img(game, px + x, py + y, 0xFF0000);
				x++;
			}
			y++;
		}
		i++;
	}
}
