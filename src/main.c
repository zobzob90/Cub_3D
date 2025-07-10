/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:17:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/04 16:23:15 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_game *game)
{
	char	tmp[MAP_HEIGHT][MAP_WIDTH + 1] = {
		"111111",
		"100011",
		"101001",
		"1000N1",
		"111111"
	};
	int		i;
	int		j;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			game->map[i][j] = tmp[i][j];
			j++;
		}
		i++;
	}
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit(1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D Lite");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		(free(game->mlx), exit(1));
	}
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	init_map(game);
	game->player.x = 3.5;
	game->player.y = 3.5;
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = FOV;
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	draw_scene(&game);
	mlx_hook(game.win, 2, 1L << 0, &handle_key, &game);
	mlx_hook(game.win, 17, 0, &close_win, &game);
	mlx_loop(game.mlx);
	return (0);
}
