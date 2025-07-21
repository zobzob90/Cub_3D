/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 08:17:17 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-15 08:17:17 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static void	set_player_position(t_map *map, int i, int j)
{
	map->player.x = (double)j + 0.5;
	map->player.y = (double)i + 0.5;
	map->player.orientation = map->grid[i][j];
	map->grid[i][j] = '0';
}

int	find_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player_char(map->grid[i][j]))
			{
				set_player_position(map, i, j);
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}
