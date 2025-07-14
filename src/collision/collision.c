/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-11 09:26:45 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-11 09:26:45 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_position(t_game *game, double x, double y)
{
	if (x >= 0 && x < game->map->width && y >= 0 && y < game->map->height)
		if (game->map->grid[(int)y][(int)x] != '1')
			return (true);
	return (false);
}

bool	can_move_to(t_game *g, double new_x, double new_y)
{
	if (!check_wall_collision(g, new_x, new_y, PLAYER_MARGIN)
		&& is_valid_position(g, new_x, new_y))
		return (true);
	return (false);
}

void	move_player_safe(t_game *g, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	new_x = g->player.x + delta_x;
	new_y = g->player.y + delta_y;
	if (can_move_to(g, new_x, new_y))
	{
		g->player.x = new_x;
		g->player.y = new_y;
		return ;
	}
	if (can_move_to(g, new_x, g->player.y))
		g->player.x = new_x;
	else if (can_move_to(g, g->player.x, new_y))
		g->player.y = new_y;
}

bool	check_wall_collision(t_game *g, double x, double y, double margin)
{
	int	check_x_min;
	int	check_x_max;
	int	check_y_min;
	int	check_y_max;

	check_x_min = (int)(x - margin);
	check_x_max = (int)(x + margin);
	check_y_min = (int)(y - margin);
	check_y_max = (int)(y + margin);
	if (check_x_min < 0 || check_x_max >= g->map->width
		|| check_y_min < 0 || check_y_max >= g->map->height)
		return (true);
	if (g->map->grid[check_y_min][check_x_min] == '1' ||
		g->map->grid[check_y_min][check_x_max] == '1' ||
		g->map->grid[check_y_max][check_x_min] == '1' ||
		g->map->grid[check_y_max][check_x_max] == '1')
		return (true);
	return (false);
}
