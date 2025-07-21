/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:31:53 by vdeliere          #+#    #+#             */
/*   Updated: 2025/07/11 16:30:06 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*Handle the key press*/
int	handle_press_key(int key, t_game *g)
{
	if (key == ESC)
		close_win(g);
	if (key == W)
		g->keys->w = true;
	if (key == S)
		g->keys->s = true;
	if (key == A)
		g->keys->a = true;
	if (key == D)
		g->keys->d = true;
	if (key == UP)
		g->keys->up = true;
	if (key == DOWN)
		g->keys->down = true;
	if (key == LEFT)
		g->keys->left = true;
	if (key == RIGHT)
		g->keys->right = true;
	if (key == CTRL_G || key == CTRL_D)
		gun_fire(g);
	return (0);
}

/*Handle the key release*/
int	handle_release_key(int key, t_game *g)
{
	if (key == W)
		g->keys->w = false;
	if (key == S)
		g->keys->s = false;
	if (key == A)
		g->keys->a = false;
	if (key == D)
		g->keys->d = false;
	if (key == UP)
		g->keys->up = false;
	if (key == DOWN)
		g->keys->down = false;
	if (key == LEFT)
		g->keys->left = false;
	if (key == RIGHT)
		g->keys->right = false;
	if (key == CTRL_G || key == CTRL_D)
		gun_stop_fire(g);
	return (0);
}
