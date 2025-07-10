/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-09 16:09:32 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-09 16:09:32 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		y++;
	}
}
