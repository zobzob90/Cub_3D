/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:31:53 by vdeliere          #+#    #+#             */
/*   Updated: 2025/07/29 13:08:25 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_control_key(int key, t_game *game)
{
	if (key == ESC)
		close_win(game);
	if (key == W)
		game->keys->w = true;
	if (key == S)
		game->keys->s = true;
	if (key == A)
		game->keys->a = true;
	if (key == D)
		game->keys->d = true;
	if (key == UP)
		game->keys->up = true;
	if (key == DOWN)
		game->keys->down = true;
	if (key == LEFT)
		game->keys->left = true;
	if (key == RIGHT)
		game->keys->right = true;
}

/*Handle the key press*/
int	handle_press_key(int key, t_game *game)
{
	if (key == SHIFT_L)
		game->keys->shift = true;
	if (key == CTRL_G || key == CTRL_D)
		gun_fire(game);
	if (key == ALT_L || key == ALT_R)
		capture_mouse(game);
	if (key == E)
		handle_door_interaction(game);
	if (key == M)
	{
		game->show_minimap = !game->show_minimap;
		printf("Minimap toggled: %d\n", game->show_minimap);
	}
	else
		handle_control_key(key, game);
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
