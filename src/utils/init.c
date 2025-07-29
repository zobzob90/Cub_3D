/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:14:51 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 15:16:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_player_from_map(t_player *player)
{
	set_player_direction(player);
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	init_texture(&map->texture);
	init_color(&map->floor);
	init_color(&map->ceiling);
	init_player(&map->player);
	map->doors = NULL;
	map->num_doors = 0;
}

static int	count_doors_in_map(t_map *map)
{
	int	i;
	int	j;
	int	door_count;

	door_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'D')
				door_count++;
			j++;
		}
		i++;
	}
	return (door_count);
}

static void	fill_doors_array(t_map *map)
{
	int	i;
	int	j;
	int	index;

	index = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'D')
			{
				map->doors[index].x = j;
				map->doors[index].y = i;
				map->doors[index].open = false;
				index++;
			}
			j++;
		}
		i++;
	}
}

void	init_doors_from_map(t_map *map)
{
	int	door_count;

	door_count = count_doors_in_map(map);
	if (door_count > 0)
	{
		map->doors = malloc(sizeof(t_door) * door_count);
		if (!map->doors)
			return ;
		map->num_doors = door_count;
		fill_doors_array(map);
	}
}
