/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:55 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 14:50:19 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	assign_texture_path_noso(char *direction, char *path, t_map *map)
{
	if (!ft_strncmp(direction, "NO", 3))
	{
		if (map->texture.no)
			return (false);
		map->texture.no = path;
	}
	else if (!ft_strncmp(direction, "SO", 3))
	{
		if (map->texture.so)
			return (false);
		map->texture.so = path;
	}
	else
		return (false);
	return (true);
}

static bool	assign_texture_path_eawe(char *direction, char *path, t_map *map)
{
	if (!ft_strncmp(direction, "EA", 3))
	{
		if (map->texture.ea)
			return (false);
		map->texture.ea = path;
	}
	else if (!ft_strncmp(direction, "WE", 3))
	{
		if (map->texture.we)
			return (false);
		map->texture.we = path;
	}
	else
		return (false);
	return (true);
}

static bool	assign_texture_path(char *direction, char *path, t_map *map)
{
	if (assign_texture_path_noso(direction, path, map))
		return (true);
	if (assign_texture_path_eawe(direction, path, map))
		return (true);
	return (false);
}

bool	parse_texture(char *line, t_map *map)
{
	char	**tokens;
	char	*path;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (false);
	i = 0;
	while (tokens[i])
		i++;
	if (i != 2)
		return (ft_free_tab(tokens), false);
	path = ft_strdup(tokens[1]);
	if (!path)
		return (ft_free_tab(tokens), false);
	if (!assign_texture_path(tokens[0], path, map))
	{
		free(path);
		ft_free_tab(tokens);
		return (false);
	}
	ft_free_tab(tokens);
	return (true);
}
