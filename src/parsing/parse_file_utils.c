/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:45:33 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 14:49:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_empty_line(char *line)
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

int	process_config_line(char *line, t_map *map, int *parsed_count)
{
	if (is_texture(line))
	{
		if (!parse_texture(line, map))
			return (ft_putstr_fd("Error\nInvalid texture\n", 2), 0);
		(*parsed_count)++;
	}
	else if (is_color(line))
	{
		if (!parse_color(line, map))
			return (ft_putstr_fd("Error\nInvalid color\n", 2), 0);
		(*parsed_count)++;
	}
	else
	{
		return (ft_putstr_fd("Error\nInvalid line in config section\n",
				2), 0);
	}
	return (1);
}

int	parse_textures_and_colors(char **lines, t_map *map)
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
			continue ;
		}
		if (!process_config_line(lines[i], map, &parsed_count))
			return (0);
		i++;
	}
	if (parsed_count != 6)
		return (ft_putstr_fd("Error\nMissing configuration elements\n",
				2), 0);
	return (i);
}

int	validate_parsing(t_map *map)
{
	if (!map->texture.no || !map->texture.so
		|| !map->texture.ea || !map->texture.we)
		return (ft_putstr_fd("Error\nMissing textures\n", 2), 0);
	if (map->floor.r == -1 || map->ceiling.r == -1)
		return (ft_putstr_fd("Error\nMissing floor or ceiling color\n", 2), 0);
	return (1);
}
