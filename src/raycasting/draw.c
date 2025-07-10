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

/*Put a pixel inside the image buffer*/
void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;
	
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = game->img_data + (y * game->size_line + x * (game->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

/*Draw a vertical line in the screen(roof + floor + wall)*/
void	draw_vertical_line(t_game *game, int x, int start, int end, int color)
{
	int	y;

	y = 0;
	while (y < start)
	{
		put_pixel_to_img(game, x, y, 0x000000);
		y++;
	}
	y = start;
	while (y < end)
	{
		put_pixel_to_img(game, x, y, color);
		y++;
	}
	y = end;
	while (y < HEIGHT)
	{
		put_pixel_to_img(game, x, y, 0x444444);
		y++;
	}
}
