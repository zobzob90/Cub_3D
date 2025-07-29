/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:14:20 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 13:14:39 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_door(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map->width || y >= game->map->height)
		return (false);
	return (game->map->grid[y][x] == 'D' || game->map->grid[y][x] == 'O');
}

t_door	*find_door(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < game->map->num_doors)
	{
		if (game->map->doors[i].x == x && game->map->doors[i].y == y)
			return (&game->map->doors[i]);
		i++;
	}
	return (NULL);
}

void	toggle_door(t_game *game, int x, int y)
{
	t_door	*door;

	door = find_door(game, x, y);
	if (door)
	{
		door->open = !door->open;
		if (door->open)
			game->map->grid[y][x] = 'O';
		else
			game->map->grid[y][x] = 'D';
	}
}
