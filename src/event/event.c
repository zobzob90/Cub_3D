/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-09 15:31:53 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-09 15:31:53 by vdeliere         ###   ########.fr       */
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
	if (key == W && g->map[(int)(g->player.y)]
		[(int)(g->player.x + g->player.dir_x * SPEED)] != '1')
		g->player.x += g->player.dir_x * SPEED;
	if (key == W && g->map[(int)(g->player.y + g->player.dir_y * SPEED)]
		[(int)(g->player.x)] != '1')
		g->player.y += g->player.dir_y * SPEED;
	if (key == 's')
	{
		if (g->map[(int)(g->player.y)]
			[(int)(g->player.x - g->player.dir_x * SPEED)] != '1')
			g->player.x -= g->player.dir_x * SPEED;
		if (g->map[(int)(g->player.y - g->player.dir_y * SPEED)]
			[(int)(g->player.x)] != '1')
			g->player.y -= g->player.dir_y * SPEED;
	}
	if (key == 'a' || key == 65361)
		rotate(g, ROT_SPEED);
	if (key == 'd' || key == 65363)
		rotate(g, -ROT_SPEED);
	mlx_clear_window(g->mlx, g->win);
	draw_scene(g);
	return (0);
}
