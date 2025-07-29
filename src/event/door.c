/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:52:07 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 13:14:35 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	check_door_at_position(t_game *game, int check_x, int check_y,
								double check_distance)
{
	double	distance;

	distance = sqrt(pow(game->player.x - check_x - 0.5, 2)
			+ pow(game->player.y - check_y - 0.5, 2));
	if (distance <= check_distance && is_door(game, check_x, check_y))
	{
		toggle_door(game, check_x, check_y);
		return (true);
	}
	return (false);
}

static bool	search_door_around_player(t_game *game, int player_x, int player_y)
{
	double	check_distance;
	int		check_x;
	int		check_y;
	int		dx;
	int		dy;

	check_distance = 1.5;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			check_x = player_x + dx;
			check_y = player_y + dy;
			if (check_door_at_position(game, check_x, check_y, check_distance))
				return (true);
			dx++;
		}
		dy++;
	}
	return (false);
}

void	handle_door_interaction(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = (int)game->player.x;
	player_y = (int)game->player.y;
	search_door_around_player(game, player_x, player_y);
}
