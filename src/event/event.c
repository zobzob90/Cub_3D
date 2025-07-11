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

void	cleanup_game(t_game *game)
{
	// Libérer les textures
	if (game->tex_north)
		mlx_destroy_image(game->mlx, game->tex_north);
	if (game->tex_south)
		mlx_destroy_image(game->mlx, game->tex_south);
	if (game->tex_east)
		mlx_destroy_image(game->mlx, game->tex_east);
	if (game->tex_west)
		mlx_destroy_image(game->mlx, game->tex_west);
	// Libérer l'image principale
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	close_win(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void	rotate(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(angle)
		- g->player.dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle)
		+ g->player.dir_y * cos(angle);
	g->player.plane_x = g->player.plane_x * cos(angle)
		- g->player.plane_y * sin(angle);
	g->player.plane_y = old_plane_x * sin(angle)
		+ g->player.plane_y * cos(angle);
}

int	handle_key(int key, t_game *g)
{
	if (key == ESC)
		close_win(g);
	if (key == W || key == UP)
		move_player_safe(g, g->player.dir_x * SPEED, g->player.dir_y * SPEED);
	if (key == S || key == DOWN)
		move_player_safe(g, -g->player.dir_x * SPEED, -g->player.dir_y * SPEED);
	if (key == A || key == LEFT)
		rotate(g, ROT_SPEED);
	if (key == D || key == RIGHT)
		rotate(g, -ROT_SPEED);
	return (0);
}
