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

int	close_win(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
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
	
	// Mouvement simplifié pour le test (sans collision)
	if (key == W)
	{
		g->player.x += g->player.dir_x * SPEED;
		g->player.y += g->player.dir_y * SPEED;
	}
	if (key == S)
	{
		g->player.x -= g->player.dir_x * SPEED;
		g->player.y -= g->player.dir_y * SPEED;
	}
	if (key == A || key == LEFT)
		rotate(g, ROT_SPEED);
	if (key == D || key == RIGHT)
		rotate(g, -ROT_SPEED);
	
	mlx_clear_window(g->mlx, g->win);
	// draw_scene(g); // TODO: Implémenter le rendu
	printf("Player position: (%.2f, %.2f)\n", g->player.x, g->player.y);
	return (0);
}
