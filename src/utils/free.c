/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:38:14 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:58 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*Free the textures and the main image*/
void	cleanup_game(t_game *game)
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
	if (game->enemy_sprite[0].img)
		mlx_destroy_image(game->mlx, game->enemy_sprite[0].img);
	if (game->enemy_sprite[1].img)
		mlx_destroy_image(game->mlx, game->enemy_sprite[1].img);
	if (game->enemy_sprite[2].img)
		mlx_destroy_image(game->mlx, game->enemy_sprite[2].img);
	free_texture(&game->map->texture);
	if (game->map->grid)
		ft_free_tab(game->map->grid);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->keys)
		free(game->keys);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
