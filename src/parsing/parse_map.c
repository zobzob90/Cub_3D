/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:48 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/11 13:08:39 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(char	**lines)
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
			continue;
		}
		if (is_map(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

void	calculate_map_dim(char **lines, int start)
{

}

void	extract_map_grid(char **lines, int start, t_map *map)
{
	
}

int	find_player(t_map *map)
{

}

int	parse_map(char **lines, t_map *map)
{
	
}
