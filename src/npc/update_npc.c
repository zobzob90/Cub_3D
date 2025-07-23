/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:57:41 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/23 17:05:27 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	npc_moving(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->map->width ||
		map_y < 0 || map_y >= game->map->height)
		return (false);
	if (game->map->grid[map_y][map_x] == '1' || game->map->grid[map_y][map_x] == 'D')
		return (false);
	return (true);
}

void	update_npc(t_game *game)
{
	int		i;
	int		new_x;
	int		new_y;
	double	dx;
	double	dy;
	double	distance;
	t_npc	*npc;
	
	i = 0;
	while (i < game->map->num_npcs)
	{
		npc = &game->map->npcs[i];
		npc->anim_timer++;
		if (npc->anim_timer >= 30)
		{
			npc->anim_frame = (npc->anim_frame + 1) % 3;
			npc->anim_timer = 0;
		}
		
		dx = game->player.x - npc->x;
		dy = game->player.y - npc->y;
		distance = sqrt(dx * dx + dy * dy);
		if (distance < 5.0)
		{
			npc->see_player = true;
			npc->dir_x = dx / distance;
			npc->dir_y = dy / distance;
			new_x = npc->x + npc->dir_x * 0.01;
			new_y = npc->y + npc->dir_y * 0.01;
			if (npc_moving(game, new_x, new_y))
			{
				npc->x = new_x;
				npc->y = new_y;
			}
		}
		else
			npc->see_player = false;
		i++;
	}
}
