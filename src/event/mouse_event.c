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

void	capture_mouse(t_game *g)
{
	if (!g->keys->lock_mouse)
	{
		mlx_mouse_hide(g->mlx, g->win);
		g->keys->lock_mouse = true;
		ft_printf("Mouse mod ON\n");
	}
	else if (g->keys->lock_mouse)
	{
		mlx_mouse_show(g->mlx, g->win);
		g->keys->lock_mouse = false;
		ft_printf("Mouse mod OFF\n");
	}
}

int	handle_mouse_move(int x, int y, t_game *g)
{
	int	delta_x;

	(void)y;
	delta_x = x - WIDTH / 2;
	if (g->keys->lock_mouse)
	{
		if (delta_x < 0)
			rotate(g, ROT_SPEED * delta_x * MOUSE_SENSITIVITY);
		else if (delta_x > 0)
			rotate(g, ROT_SPEED * abs(delta_x) * MOUSE_SENSITIVITY);
	}
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT && g->keys->lock_mouse)
		gun_fire(g);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT && g->keys->lock_mouse)
		gun_stop_fire(g);
	return (0);
}
