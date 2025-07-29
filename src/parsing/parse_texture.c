/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:08:55 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 17:30:24 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	validate_tokens(char **tokens)
{
	int	i;

	if (!tokens || !tokens[0] || !tokens[1])
		return (false);
	i = 0;
	while (tokens[i])
		i++;
	if (i != 2)
		return (false);
	return (true);
}

static bool	validate_texture_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid path texture\n", 2);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	handle_assign_result(int result, char *path, char **tokens)
{
	if (result == -1)
	{
		ft_putstr_fd("Error\nDuplicate texture element\n", 2);
		free(path);
		ft_free_tab(tokens);
		return (false);
	}
	else if (result == 0)
	{
		ft_putstr_fd("Error\nInvalid texture direction\n", 2);
		free(path);
		ft_free_tab(tokens);
		return (false);
	}
	return (true);
}

bool	parse_texture(char *line, t_map *map)
{
	char	**tokens;
	char	*path;
	int		result;

	tokens = ft_split(line, ' ');
	if (!validate_tokens(tokens))
		return (ft_free_tab(tokens), false);
	path = ft_strdup(tokens[1]);
	if (!path)
		return (ft_free_tab(tokens), false);
	if (!validate_texture_file(path))
	{
		free(path);
		ft_free_tab(tokens);
		return (false);
	}
	result = assign_texture_path(tokens[0], path, map);
	if (!handle_assign_result(result, path, tokens))
		return (false);
	ft_free_tab(tokens);
	return (true);
}
