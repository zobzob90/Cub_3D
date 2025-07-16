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

int	update_player_movement(t_game *g)
{
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