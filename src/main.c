/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:17:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 17:20:49 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Clean close of the game*/
int	close_win(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2), 1);
	if (!check_file_extension(argv[1]))
		return (ft_putstr_fd("Error\nInvalid file extension : Please use .cub files.\n", 2), 1);
	if (!parse_file(argv[1], &map))
		return (ft_putstr_fd("Error\nFailed to parse file\n", 2), 1);
	init_game(&game);
	game.player = map.player;
	init_player_from_map(&game.player);
	game.map = &map;
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img_data = mlx_get_data_addr(game.img,
			&game.bpp, &game.size_line, &game.endian);
	load_textures(&game);
	load_pig_sprite(&game);
	draw_scene(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_press_key, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_release_key, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_hook(game.win, 4, 1L << 2, handle_mouse_press, &game);
	mlx_hook(game.win, 6, 1L << 6, handle_mouse_move, &game);
	mlx_loop_hook(game.mlx, update_player_movement, &game);
	mlx_loop(game.mlx);
	return (free_map(&map), 0);
}
