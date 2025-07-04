/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:38:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/04 11:01:23 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_texture *texture)
{
	if (texture->no)
		free(texture->no);
	if (texture->so)
		free(texture->so);
	if (texture->we)
		free(texture->we);
	if (texture->ea)
		free(texture->ea);
}

void	free_map(t_map *map)
{
	if (map->grid)
		ft_free_tab(map->grid);
	free_texture(&map->texture);
}

void	free_all(t_map *map)
{
	free_map(map);
}
