/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:21:18 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/23 14:01:37 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_game *game)
{
	game->keys = malloc(sizeof(t_keys));
	if (!game->keys)
		return ;
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
	gun->tex_repos = "texture/xpm/gun/gun.xpm";
	gun->tex_fire = "texture/xpm/gun/gun_fire_1.xpm";
	gun->tex_bpp = 0;
	gun->tex_data = 0;
	gun->tex_endian = 0;
	gun->tex_height = 0;
	gun->tex_width = 0;
	gun->tex_size_line = 0;
	gun->fire_timer = 0;
	gun->fire_duration = 5;
}

/*Initialisation of the game struct*/
void	init_game(t_game *game)
{
	game->bpp = 0;
	game->endian = 0;
	game->img = 0;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D Lite");
	game->size_line = 0;
	game->tex_bpp = 32;
	game->tex_east = 0;
	game->tex_east_data = 0;
	game->tex_endian = 0;
	game->tex_height = 0;
	game->tex_north = 0;
	game->tex_north_data = 0;
	game->tex_size_line = WIDTH;
	game->tex_south = 0;
	game->tex_south_data = 0;
	game->tex_west = 0;
	game->tex_west_data = 0;
	game->tex_width = 0;
	init_keys(game);
	init_gun(&game->gun);
	load_pig_sprite(game);
	game->show_minimap = true;
}
