/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:55 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/10 13:23:04 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_texture(char *line, t_map *map)
{
	char	**tokens;
	char	*path;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (false);
	path = ft_strdup(tokens[1]);
	if (!path)
		return (ft_free_tab(tokens), false);
	if (!ft_strncmp(tokens[0], "NO", 3))
		map->texture.no = path;
	else if (!ft_strncmp(tokens[0], "SO", 3))
		map->texture.so = path;
	else if (!ft_strncmp(tokens[0], "EA", 3))
		map->texture.ea = path;
	else if (!ft_strncmp(tokens[0], "WE", 3))
		map->texture.we = path;
	else
	{
		free(path);
		ft_free_tab(tokens);
		return (false);
	}
	ft_free_tab(tokens);
	return (true);
}
