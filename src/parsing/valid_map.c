/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:13:33 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/10 16:40:55 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_borders(t_map *map)
{
	int	i;
	int	widht;
	int	height;

	i = 0;
	widht = map->width;
	height = map->height;
	//check ligne du haut
	while (i < widht)
	{
		if (map->grid[0][i] != '1' && map->grid[0][i] != ' ')
			return (false);
		i++;
	}
	//ligne du bas
	i = 0;
	while (i < widht)
	{
		if (map->grid[i][height - 1] != '1' && map->grid[i][height - 1] != ' ')
			return (false);
		i++;
	}
	return (true);
}

static bool	check_sides(t_map *map)
{
	int	y;
	int	width;
	int	height;

	height = map->height;
	y = 0;
	while (y < height)
	{
		width = ft_strlen(map->grid[y]);
		if (map->grid[y][0] != '1' && map->grid[y][0] != ' ')
			return (false);
		if (map->grid[y][width - 1] != -1 && map->grid[y][width - 1] != ' ')
			return (false);
	}
	return (true);
}

bool	check_spaces(t_map *map)
{

}

bool	is_valid_map(t_map *map)
{

}
