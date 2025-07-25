/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:31:53 by vdeliere          #+#    #+#             */
/*   Updated: 2025/07/23 15:28:27 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (key == SHIFT_L)
		g->keys->shift = true;
	if (key == CTRL_G || key == CTRL_D)
		gun_fire(g);
	if (key == ALT_L || key == ALT_R)
		capture_mouse(g);
	if (key == E)
		handle_door_interaction(g);
	if (key == M)
	{
		g->show_minimap = !g->show_minimap;
		printf("Minimap toggled: %d\n", g->show_minimap);
	}
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
	if (key == SHIFT_L)
		g->keys->shift = false;
	return (0);
}
