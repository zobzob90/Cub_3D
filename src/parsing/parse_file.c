/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:39 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 14:28:49 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_file_content(char **lines, t_map *map)
{
	int	config_end;

	config_end = parse_textures_and_colors(lines, map);
	if (!config_end)
	{
		free_texture(&map->texture);
		return (0);
	}
	if (!parse_map(lines, map))
		return (0);
	if (!validate_parsing(map))
		return (0);
	init_doors_from_map(map);
	init_npcs_from_map(map);
	return (1);
}

int	parse_file(char *filename, t_map *map)
{
	char	**lines;
	int		result;

	lines = read_files(filename);
	if (!lines)
		return (ft_putstr_fd("Error\nCannot read file\n", 2), 0);
	if (!check_file_extension(filename))
	{
		ft_free_tab(lines);
		return (ft_putstr_fd("Error\nInvalid file extension.\n", 2), 0);
	}
	init_map(map);
	result = parse_file_content(lines, map);
	ft_free_tab(lines);
	return (result);
}
