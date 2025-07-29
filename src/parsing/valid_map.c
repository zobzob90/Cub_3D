/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:13:33 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 13:29:25 by ertrigna         ###   ########.fr       */
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
	while (i < widht)
	{
		if (map->grid[0][i] != '1' && map->grid[0][i] != ' ')
			return (false);
		i++;
	}
	i = 0;
	while (i < widht)
	{
		if (map->grid[height - 1][i] != '1' && map->grid[height - 1][i] != ' ')
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
		if (map->grid[y][width - 1] != '1' && map->grid[y][width - 1] != ' ')
			return (false);
		y++;
	}
	return (true);
}

static bool	check_inside(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	while (i < map->height - 1)
	{
		j = 1;
		while (j < map->width - 1)
		{
			if (map->grid[i][j] == '0' || map->grid[i][j] == 'N'
				|| map->grid[i][j] == 'S' || map->grid[i][j] == 'O'
				|| map->grid[i][j] == 'X'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'D')
			{
				if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' '
					|| map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (1);
	return (0);
}

bool	is_valid_map(t_map *map)
{
	if (!check_borders(map))
		return (false);
	if (!check_sides(map))
		return (false);
	if (!check_inside(map))
		return (false);
	return (true);
}
