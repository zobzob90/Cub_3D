/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:52:07 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/21 15:16:55 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

void	handle_door_interaction(t_game *game)
{
	int		player_x;
	int		player_y;
	double	check_distance;
	int		check_x;
	int		check_y;
	int		dx;
	int		dy;
	double	distance;

	player_x = (int)game->player.x;
	player_y = (int)game->player.y;
	check_distance = 1.5;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			check_x = player_x + dx;
			check_y = player_y + dy;
			distance = sqrt(pow(game->player.x - check_x - 0.5, 2) + 
							pow(game->player.y - check_y - 0.5, 2));
			if (distance <= check_distance && is_door(game, check_x, check_y))
			{
				toggle_door(game, check_x, check_y);
				return ;
			}
			dx++;
		}
		dy++;
	}
}
