/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:29:28 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 17:29:56 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	assign_texture_path_noso(char *direction, char *path, t_map *map)
{
	if (!ft_strncmp(direction, "NO", 3))
	{
		if (map->texture.no)
			return (-1);
		map->texture.no = path;
	}
	else if (!ft_strncmp(direction, "SO", 3))
	{
		if (map->texture.so)
			return (-1);
		map->texture.so = path;
	}
	else
		return (0);
	return (1);
}

int	assign_texture_path_eawe(char *direction, char *path, t_map *map)
{
	if (!ft_strncmp(direction, "EA", 3))
	{
		if (map->texture.ea)
			return (-1);
		map->texture.ea = path;
	}
	else if (!ft_strncmp(direction, "WE", 3))
	{
		if (map->texture.we)
			return (-1);
		map->texture.we = path;
	}
	else
		return (0);
	return (1);
}

int	assign_texture_path(char *direction, char *path, t_map *map)
{
	int	result;

	result = assign_texture_path_noso(direction, path, map);
	if (result != 0)
		return (result);
	result = assign_texture_path_eawe(direction, path, map);
	if (result != 0)
		return (result);
	return (0);
}
