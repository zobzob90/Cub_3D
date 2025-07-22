/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:39 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 14:02:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_textures_and_colors(char **lines, t_map *map)
{
	int	i;
	int	parsed_count;

	i = 0;
	parsed_count = 0;
	while (lines[i] && parsed_count < 6)
	{
		if (is_empty_line(lines[i]))
		{
			i++;
			continue;
		}
		if (is_texture(lines[i]))
		{
			if (!parse_texture(lines[i], map))
				return (ft_putstr_fd("Error\nInvalid texture\n", 2), 0);
			parsed_count++;
		}
		else if (is_color(lines[i]))
		{
			if (!parse_color(lines[i], map))
				return (ft_putstr_fd("Error\nInvalid color\n", 2), 0);
			parsed_count++;
		}
		else
		{
			return (ft_putstr_fd("Error\nInvalid line in configuration section\n", 2), 0);
		}
		i++;
	}
	if (parsed_count != 6)
		return (ft_putstr_fd("Error\nMissing configuration elements\n", 2), 0);
	return (i);
}

static int	validate_parsing(t_map *map)
{
	if (!map->texture.no || !map->texture.so
		|| !map->texture.ea || !map->texture.we)
		return (ft_putstr_fd("Error\nMissing textures\n", 2), 0);
	if (map->floor.r == -1 || map->ceiling.r == -1)
		return (ft_putstr_fd("Error\nMissing floor or ceiling color\n", 2), 0);
	return (1);
}

int	parse_file(char *filename, t_map *map)
{
	char	**lines;
	int		config_end;

	lines = read_files(filename);
	if (!lines)
		return (ft_putstr_fd("Error\nCannot read file\n", 2), 0);
	init_map(map);
	config_end = parse_textures_and_colors(lines, map);
	if (!config_end)
	{
		ft_free_tab(lines);
		free_texture(&map->texture);
		return (0);
	}
	if (!parse_map(lines, map))
	{
		ft_free_tab(lines);
		return (0);
	}
	if (!validate_parsing(map))
	{
		ft_free_tab(lines);
		return (0);
	}
	init_doors_from_map(map);
	ft_free_tab(lines);
	return (1);
}
