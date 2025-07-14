/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:17:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/11 17:09:33 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Initialisation of the game struct*/
void	init_game(t_game *game)
{
	game->bpp = 0;
	game->endian = 0;
	game->img = 0;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D Lite");
	game->size_line = 0;
	game->tex_bpp = 0;
	game->tex_east = 0;
	game->tex_east_data = 0;
	game->tex_endian = 0;
	game->tex_height = 0;
	game->tex_north = 0;
	game->tex_north_data = 0;
	game->tex_size_line = 0;
	game->tex_south = 0;
	game->tex_south_data = 0;
	game->tex_west = 0;
	game->tex_west_data = 0;
	game->tex_width = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2), 1);
	if (!parse_file(argv[1], &map))
		return (ft_putstr_fd("Error: Failed to parse file\n", 2), 1);
	init_game(&game);
	game.player = map.player;
	init_player_from_map(&game.player);
	game.map = &map;
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);
	load_textures(&game);
	draw_scene(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop(game.mlx);
	free_map(&map);
	return (0);
}
