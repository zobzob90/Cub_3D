/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 11:41:28 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-16 11:41:28 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Handle the rotation moves*/
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

int	update_player_movement(t_game *g)
{
	if (g->keys->lock_mouse)
		mlx_mouse_move(g->mlx, g->win, WIDTH / 2, HEIGHT / 2);
	if (g->keys->w || g->keys->up)
		move_player_safe(g, g->player.dir_x * SPEED, g->player.dir_y * SPEED);
	if (g->keys->s || g->keys->down)
		move_player_safe(g, -g->player.dir_x * SPEED, -g->player.dir_y * SPEED);
	if (g->keys->a || g->keys->left)
		rotate(g, -ROT_SPEED);
	if (g->keys->d || g->keys->right)
		rotate(g, ROT_SPEED);
	draw_scene(g);
	return (0);
}
