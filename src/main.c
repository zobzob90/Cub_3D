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

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D Lite");
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	if (!parse_file(argv[1], &map))
	{
		ft_putstr_fd("Error: Failed to parse file\n", 2);
		return (1);
	}
	game.player = map.player;
	game.map = &map;  // Pointer vers la map parsée
	init_game(&game);
	printf("Map parsed successfully!\n");
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop(game.mlx);
	free_map(&map);
	return (0);
}
