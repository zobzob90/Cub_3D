/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-18 16:19:31 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-18 16:19:31 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse_move(int x, int y, t_game *g)
{
	static int	last_x;
	int			delta_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	if (delta_x < 0)
		rotate(g, ROT_SPEED * delta_x * MOUSE_SENSITIVITY);
	else if (delta_x > 0)
		rotate(g, ROT_SPEED * abs(delta_x) * MOUSE_SENSITIVITY);
	last_x = x;
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

int handle_mouse_release(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		gun_stop_fire(g);
	return (0);
}