/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:19:31 by vdeliere          #+#    #+#             */
/*   Updated: 2025/07/21 15:15:17 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse_move(int x, int y, t_game *g)
{
	int	delta_x;

	(void)y;
	delta_x = x - WIDTH / 2;
	if (delta_x < 0)
		rotate(g, ROT_SPEED * delta_x * MOUSE_SENSITIVITY);
	else if (delta_x > 0)
		rotate(g, ROT_SPEED * abs(delta_x) * MOUSE_SENSITIVITY);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		gun_fire(g);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		gun_stop_fire(g);
	return (0);
}
