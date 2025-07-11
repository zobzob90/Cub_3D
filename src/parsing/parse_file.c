/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:39 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/11 16:52:52 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_textures_and_colors(char **lines, t_map *map)
{
	int	i;
	int	parsed_count;

	i = 0;
	parsed_count = 0;
	while (lines[i] && parsed_count < 6)
	{
		if (is_texture(lines[i]))
		{
			if (!parse_texture(lines[i], map))
				return (ft_putstr_fd("Error: Invalid texture\n", 2), 0);
			parsed_count++;
		}
		else if (is_color(lines[i]))
		{
			if (!parse_color(lines[i], map))
				return (ft_putstr_fd("Error: Invalid color\n", 2), 0);
			parsed_count++;
		}
		i++;
	}
	if (parsed_count == 6)
		return (1);
	return (0);
}

static int	validate_parsing(t_map *map)
{
	if (!map->texture.no || !map->texture.so || 
		!map->texture.ea || !map->texture.we)
		return (ft_putstr_fd("Error: Missing textures\n", 2), 0);
	return (1);
}

int	parse_file(char *filename, t_map *map)
{
	char	**lines;

	lines = read_files(filename);
	if (!lines)
		return (ft_putstr_fd("Error: Cannot read file\n", 2), 0);
	init_map(map);
	if (!parse_textures_and_colors(lines, map))
	{
		ft_free_tab(lines);
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
	ft_free_tab(lines);
	return (1);
}
