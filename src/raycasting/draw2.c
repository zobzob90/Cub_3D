/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-15 08:39:19 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-15 08:39:19 by vdeliere         ###   ########.fr       */
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
		*(unsigned int *)dst = color;
	}
}
