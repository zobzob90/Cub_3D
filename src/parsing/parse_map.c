/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:48 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/11 15:53:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_map_start(char	**lines)
{
	int	i;

	i = 0;
	if (!lines)
		return (-1);
	while (lines[i])
	{
		if (!lines[i] || lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (is_texture(lines[i]) || is_color(lines[i]))
		{
			i++;
			continue;
		}
		if (is_map(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static void	calculate_map_dim(char **lines, int start, t_map *map)
{
	int	i;
	int	width;
	int	height;
	int	current_width;

	height = 0;
	width = 0;
	i = start;
	while (lines[i] && is_map(lines[i]))
	{
		current_width = ft_strlen(lines[i]);
		if (current_width > width)
			width = current_width;
		height++;
		i++;
	}
	map->height = height;
	map->width = width;
}

static int	extract_map_grid(char **lines, int start, t_map *map)
{
	int	i;
	int	j;
	int	line_lenght;

	map->grid = malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->grid[i])
		{
			while (--i >= 0)
				free(map->grid[i]);
			free(map->grid);
			return (NULL);
		}
		line_lenght = ft_strlen(lines[start + i]);
		j = 0;
		while (j < map->width)
		{
			if (j < line_lenght)
				map->grid[i][j] = lines[start + i][j];
			else
				map->grid[i][j] = ' ';
			j++;
		}
		map->grid[i][map->width] = '\0';
		i++;
	}
	return (0);
}

static int	find_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	(player_count = 0, i = 0);
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' || map->grid[i][j] == 'W' || map->grid[i][j] == 'E')
			{
				map->player.x = (double)j;
				map->player.y = (double)i;
				map->player.orientation = map->grid[i][j];
				map->grid[i][j] = '0';
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}

int	parse_map(char **lines, t_map *map)
{
	int	start;

	start = find_map_start(lines);
	if(start == -1)
		return (ft_putstr_fd("Error: No map found in file\n", 2), 0);
	calculate_map_dim(lines, start, map);
	if (map->height == 0 || map->width == 0)
		return (ft_putstr_fd("Error: Invalid map dimesions\n", 2), 0);
	if (!extract_map_grid(lines, start, map))
		return (ft_putstr_fd("Error: Failed to extract map grid\n", 2), 0);
	if (!find_player(map))
		return (ft_putstr_fd("Error : Invalid number of player\n", 2), 0);
	if (!is_valid_map(map))
		return (ft_putstr_fd("Error: Map is invalid\n", 2), 0);
	return (1);
}
