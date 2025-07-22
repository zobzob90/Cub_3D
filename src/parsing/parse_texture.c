/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:55 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 13:55:03 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_texture(char *line, t_map *map)
{
	char	**tokens;
	char	*path;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (false);
	// Vérifier qu'il n'y a que 2 éléments
	i = 0;
	while (tokens[i])
		i++;
	if (i != 2)
		return (ft_free_tab(tokens), false);
	path = ft_strdup(tokens[1]);
	if (!path)
		return (ft_free_tab(tokens), false);
	if (!ft_strncmp(tokens[0], "NO", 3))
	{
		if (map->texture.no) // Déjà défini
			return (free(path), ft_free_tab(tokens), false);
		map->texture.no = path;
	}
	else if (!ft_strncmp(tokens[0], "SO", 3))
	{
		if (map->texture.so) // Déjà défini
			return (free(path), ft_free_tab(tokens), false);
		map->texture.so = path;
	}
	else if (!ft_strncmp(tokens[0], "EA", 3))
	{
		if (map->texture.ea) // Déjà défini
			return (free(path), ft_free_tab(tokens), false);
		map->texture.ea = path;
	}
	else if (!ft_strncmp(tokens[0], "WE", 3))
	{
		if (map->texture.we) // Déjà défini
			return (free(path), ft_free_tab(tokens), false);
		map->texture.we = path;
	}
	else
	{
		free(path);
		ft_free_tab(tokens);
		return (false);
	}
	ft_free_tab(tokens);
	return (true);
}
