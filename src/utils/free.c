/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:38:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 16:52:15 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_texture(t_texture *texture)
{
	if (texture->no)
		free(texture->no);
	if (texture->so)
		free(texture->so);
	if (texture->we)
		free(texture->we);
	if (texture->ea)
		free(texture->ea);
}

void	free_map(t_map *map)
{
	if (map->grid)
		ft_free_tab(map->grid);
	if (map->doors)
		free(map->doors);
	if (map->npcs)
		free(map->npcs);
	free_texture(&map->texture);
}

static void	cleanup_game_utils(t_game *game)
{
	if (game->tex_north)
		mlx_destroy_image(game->mlx, game->tex_north);
	if (game->tex_south)
		mlx_destroy_image(game->mlx, game->tex_south);
	if (game->tex_east)
		mlx_destroy_image(game->mlx, game->tex_east);
	if (game->tex_west)
		mlx_destroy_image(game->mlx, game->tex_west);
	if (game->gun.img)
		mlx_destroy_image(game->mlx, game->gun.img);
	if (game->sprite[0].img)
		mlx_destroy_image(game->mlx, game->sprite[0].img);
	if (game->sprite[1].img)
		mlx_destroy_image(game->mlx, game->sprite[1].img);
	if (game->sprite[2].img)
		mlx_destroy_image(game->mlx, game->sprite[2].img);
	free_texture(&game->map->texture);
}

/*Free the textures and the main image*/
void	cleanup_game(t_game *game)
{
	cleanup_game_utils(game);
	if (game->map->grid)
		ft_free_tab(game->map->grid);
	if (game->map->doors)
		free(game->map->doors);
	if (game->map->npcs)
		free(game->map->npcs);
	if (game->keys && game->keys->lock_mouse && game->win && game->mlx)
	{
		mlx_mouse_show(game->mlx, game->win);
		game->keys->lock_mouse = false;
	}
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win && game->mlx)
	{
		(mlx_do_sync(game->mlx), mlx_destroy_window(game->mlx, game->win));
	}
	if (game->keys)
		free(game->keys);
	if (game->mlx)
	{
		(mlx_destroy_display(game->mlx), free(game->mlx));
	}
}
