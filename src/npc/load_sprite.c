/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:26:32 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/23 17:32:50 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_first_sprite(t_game *game)
{
	game->sprite[0].img = mlx_xpm_file_to_image(game->mlx,
		"./texture/xpm/npc/pig_walking.xpm",
		&game->sprite[0].width, &game->sprite[0].height);
	if (game->sprite[0].img)
	{
		game->sprite[0].img_data = mlx_get_data_addr(game->sprite[0].img,
				&game->sprite[0].bpp, &game->sprite[0].size_line,
				&game->sprite[0].endian);
	}
}

static void	load_second_sprite(t_game *game)
{
	game->sprite[1].img = mlx_xpm_file_to_image(game->mlx, "./texture/xpm/npc/pig_walking_2.xpm", 
		&game->sprite[1].width, &game->sprite[1].height);
	if (game->sprite[1].img)
	{
		game->sprite[1].img_data = mlx_get_data_addr(game->sprite[1].img, 
			&game->sprite[1].bpp, &game->sprite[1].size_line, &game->sprite[1].endian);
	}
}

static void	load_third_sprite(t_game *game)
{
	game->sprite[2].img = mlx_xpm_file_to_image(game->mlx, "./texture/xpm/npc/pig_walking_3.xpm", 
			&game->sprite[2].width, &game->sprite[2].height);
	if (game->sprite[2].img)
	{
		game->sprite[2].img_data = mlx_get_data_addr(game->sprite[2].img, 
				&game->sprite[2].bpp,
				&game->sprite[2].size_line, &game->sprite[2].endian);
	}
}

void	load_pig_sprite(t_game *game)
{
	load_first_sprite(game);
	load_second_sprite(game);
	load_third_sprite(game);
}
