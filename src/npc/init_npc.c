/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:17:16 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 17:18:44 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_npc(t_npc *npc)
{
	npc->x = 0;
	npc->y = 0;
	npc->dir_x = 1;
	npc->dir_y = 0;
	npc->hp = 100;
	npc->type = 0;
	npc->see_player = false;
}

static	int	count_npc(t_map *map)
{
	int	i;
	int	j;
	int	npc_count;

	i = 0;
	npc_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'X')
				npc_count++;
			j++;
		}
		i++;
	}
	return (npc_count);
}

static void	place_npc(t_map *map)
{
	int	i;
	int	j;
	int	npc_count;

	npc_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'X')
			{
				init_npc(&map->npcs[npc_count]);
				map->npcs[npc_count].x = j + 0.5;
				map->npcs[npc_count].y = i + 0.5;
				map->grid[i][j] = '0';
				npc_count++;
			}
			j++;
		}
		i++;
	}
}

void	init_npcs_from_map(t_map *map)
{
	map->num_npcs = count_npc(map);
	if (map->num_npcs == 0)
	{
		map->npcs = NULL;
		return ;
	}
	map->npcs = malloc(sizeof(t_npc) * map->num_npcs);
	if (!map->npcs)
		return ;
	place_npc(map);
}
