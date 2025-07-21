/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 08:20:22 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-15 08:20:22 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_partial_grid(char **grid, int count)
{
	while (--count >= 0)
		free(grid[count]);
	free(grid);
}

static int	allocate_grid_row(t_map *map, int i)
{
	map->grid[i] = malloc(sizeof(char) * (map->width + 1));
	if (!map->grid[i])
	{
		free_partial_grid(map->grid, i);
		return (0);
	}
	return (1);
}

static void	fill_grid_row(t_map *map, char **lines, int start, int i)
{
	int	j;
	int	line_lenght;

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
}

int	extract_map_grid(char **lines, int start, t_map *map)
{
	int	i;

	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!allocate_grid_row(map, i))
			return (0);
		fill_grid_row(map, lines, start, i);
		i++;
	}
	map->grid[map->height] = NULL;
	return (1);
}
