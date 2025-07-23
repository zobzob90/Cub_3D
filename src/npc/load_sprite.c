
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:28:52 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/23 15:28:27 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_pig_sprite(t_game *game)
{
	game->enemy_sprite[0].img = mlx_xpm_file_to_image(game->mlx, "./texture/xpm/npc/pig_walking.xpm", 
		&game->enemy_sprite[0].width, &game->enemy_sprite[0].height);
	if (game->enemy_sprite[0].img)
	{
		game->enemy_sprite[0].img_data = mlx_get_data_addr(game->enemy_sprite[0].img, 
			&game->enemy_sprite[0].bpp, &game->enemy_sprite[0].size_line, &game->enemy_sprite[0].endian);
	}
	game->enemy_sprite[1].img = mlx_xpm_file_to_image(game->mlx, "./texture/xpm/npc/pig_walking_2.xpm", 
		&game->enemy_sprite[1].width, &game->enemy_sprite[1].height);
	if (game->enemy_sprite[1].img)
	{
		game->enemy_sprite[1].img_data = mlx_get_data_addr(game->enemy_sprite[1].img, 
			&game->enemy_sprite[1].bpp, &game->enemy_sprite[1].size_line, &game->enemy_sprite[1].endian);
	}
	game->enemy_sprite[2].img = mlx_xpm_file_to_image(game->mlx, "./texture/xpm/npc/pig_walking_3.xpm", 
		&game->enemy_sprite[2].width, &game->enemy_sprite[2].height);
	if (game->enemy_sprite[2].img)
	{
		game->enemy_sprite[2].img_data = mlx_get_data_addr(game->enemy_sprite[2].img, 
			&game->enemy_sprite[2].bpp, &game->enemy_sprite[2].size_line, &game->enemy_sprite[2].endian);
	}
}
