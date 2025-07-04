/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:24 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/04 15:42:19 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_color(int value)
{
	return (value >= 0 && value <= 255);
}

static int	parse_rgb(char *str, t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_free_tab(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (!is_valid_color(r) || !is_valid_color(g) || !is_valid_color(b))
		return (ft_free_tab(rgb), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	ft_free_tab(rgb);
	return (1);
}

bool	parse_color(char *line, t_map *map)
{
	char	**tokens;
	t_color	color;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (ft_free_tab(tokens), false);
	if (!parse_rgb(tokens[1], &color))
		return (ft_free_tab(tokens), false);
	if (!ft_strncmp(tokens[0], "F", 1))
		map->floor = color;
	else if (!ft_strncmp(tokens[0], "C", 1))
		map->ceiling = color;
	else
		return (ft_free_tab(tokens), false);
	ft_free_tab(tokens);
	return (true);
}
