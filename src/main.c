/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:17:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/22 14:11:13 by ertrigna         ###   ########.fr       */
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

static void	init_keys(t_game *game)
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

static void	init_gun(t_weapon *gun)
{
	gun->img = NULL;
	gun->tex_repos = "texture/xpm/gun.xpm";
	gun->tex_fire = "texture/xpm/gun_fire_1.xpm";
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
	game->show_minimap = true;
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
