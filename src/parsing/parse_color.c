/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:24 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 14:37:51 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	is_valid_color(int value)
{
	return (value >= 0 && value <= 255);
}

static int	is_val_numb(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb(char *str, t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (ft_free_tab(rgb), 0);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
		return (ft_free_tab(rgb), 0);
	if (!is_val_numb(rgb[0]) || !is_val_numb(rgb[1]) || !is_val_numb(rgb[2]))
		return (ft_free_tab(rgb), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (!is_valid_color(r) || !is_valid_color(g) || !is_valid_color(b))
		return (ft_free_tab(rgb), 0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (ft_free_tab(rgb), 1);
}

static bool	assign_color_to_map(char *type, t_color color, t_map *map)
{
	if (!ft_strncmp(type, "F", 1))
	{
		if (map->floor.r != -1)
			return (false);
		map->floor = color;
	}
	else if (!ft_strncmp(type, "C", 1))
	{
		if (map->ceiling.r != -1)
			return (false);
		map->ceiling = color;
	}
	else
		return (false);
	return (true);
}

bool	parse_color(char *line, t_map *map)
{
	char	**tokens;
	t_color	color;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (ft_free_tab(tokens), false);
	i = 0;
	while (tokens[i])
		i++;
	if (i != 2)
		return (ft_free_tab(tokens), false);
	if (!parse_rgb(tokens[1], &color))
		return (ft_free_tab(tokens), false);
	if (!assign_color_to_map(tokens[0], color, map))
		return (ft_free_tab(tokens), false);
	ft_free_tab(tokens);
	return (true);
}
