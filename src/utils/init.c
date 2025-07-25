/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:14:51 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/21 15:33:53 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_texture(t_texture *texture)
{
	texture->no = NULL;
	texture->so = NULL;
	texture->we = NULL;
	texture->ea = NULL;
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->orientation = '\0';
}

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

void	init_doors_from_map(t_map *map)
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
	if (door_count > 0)
	{
		map->doors = malloc(sizeof(t_door) * door_count);
		if (!map->doors)
			return;
		map->num_doors = door_count;
		door_count = 0;
		i = 0;
		while (i < map->height)
		{
			j = 0;
			while (j < map->width)
			{
				if (map->grid[i][j] == 'D')
				{
					map->doors[door_count].x = j;
					map->doors[door_count].y = i;
					map->doors[door_count].open = false;
					door_count++;
				}
				j++;
			}
			i++;
		}
	}
}
