/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:14:51 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/10 14:56:05 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_texture(t_texture *texture)
{
	texture->no = NULL;
	texture->so = NULL;
	texture->we = NULL;
	texture->ea = NULL;
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->orientation = '\0';
}

static void	set_north_direction(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

static void	set_south_direction(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

static void	set_east_direction(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

static void	set_west_direction(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

static void	set_player_direction(t_player *player)
{
	if (player->orientation == 'N')
		set_north_direction(player);
	else if (player->orientation == 'S')
		set_south_direction(player);
	else if (player->orientation == 'E')
		set_east_direction(player);
	else if (player->orientation == 'W')
		set_west_direction(player);
}

void	init_player_from_map(t_player *player)
{
	set_player_direction(player);
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	init_texture(&map->texture);
	init_color(&map->floor);
	init_color(&map->ceiling);
	init_player(&map->player);
}
