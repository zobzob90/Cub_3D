/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:48 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 14:36:45 by ertrigna         ###   ########.fr       */
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
			continue ;
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

static int	validate_after_map(char **lines, int start, int map_height)
{
	int	i;
	int	j;

	i = start + map_height;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] != ' ' && lines[i][j] != '\t'
					&& lines[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(char **lines, t_map *map)
{
	int	start;

	start = find_map_start(lines);
	if (start == -1)
		return (ft_putstr_fd("Error\nNo map found in file\n", 2), 0);
	calculate_map_dim(lines, start, map);
	if (map->height == 0 || map->width == 0)
		return (ft_putstr_fd("Error\nInvalid map dimesions\n", 2), 0);
	if (!validate_after_map(lines, start, map->height))
	{
		free_texture(&map->texture);
		return (ft_putstr_fd("Error\nInvalid content after map\n", 2), 0);
	}
	if (!extract_map_grid(lines, start, map))
		return (ft_putstr_fd("Error\nFailed to extract map grid\n", 2), 0);
	if (!find_player(map))
	{
		free_texture(&map->texture);
		ft_free_tab(map->grid);
		return (ft_putstr_fd("Error\nInvalid number of player\n", 2), 0);
	}
	if (!is_valid_map(map))
	{
		free_texture(&map->texture);
		ft_free_tab(map->grid);
		return (ft_putstr_fd("Error\nMap is invalid\n", 2), 0);
	}
	return (1);
}
