/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:45:00 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/29 17:19:26 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_player_direction_n_s(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->orientation == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

void	set_player_direction(t_player *player)
{
	set_player_direction_n_s(player);
	if (player->orientation == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->orientation == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	init_keys(t_game *game)
{
	game->keys->w = false;
	game->keys->s = false;
	game->keys->a = false;
	game->keys->d = false;
	game->keys->up = false;
	game->keys->down = false;
	game->keys->left = false;
	game->keys->right = false;
	game->keys->lock_mouse = false;
	game->keys->shift = false;
}

void	init_gun(t_weapon *gun)
{
	gun->img = NULL;
	gun->tex_repos = NULL;
	gun->tex_fire = NULL;
	gun->tex_height = 0;
	gun->tex_width = 0;
	gun->tex_data = NULL;
	gun->tex_size_line = 0;
	gun->tex_bpp = 0;
	gun->tex_endian = 0;
	gun->fire_timer = 0;
	gun->fire_duration = 0;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->img_data = NULL;
	game->bpp = 0;
	game->size_line = 0;
	game->endian = 0;
	game->show_minimap = true;
}
