/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:32:03 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 14:27:50 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_pixel_from_sprite(t_sprite *sprite, int x, int y)
{
	int	color;
	int	index;

	if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
		return (0);
	index = y * sprite->size_line + x * (sprite->bpp / 8);
	color = *(unsigned int *)(sprite->img_data + index);
	return (color);
}

int	is_transparent_pixel(int color)
{
	unsigned char	alpha;

	alpha = (color >> 24) & 0xFF;
	if (alpha == 0)
		return (1);
	if ((color & 0x00FFFFFF) == 0x00FF00FF)
		return (1);
	return (0);
}

void	draw_sprite_column(t_game *game, int sprite_screen_x,
						int sprite_height, int sprite_width)
{
	t_sprite_draw	draw;

	init_sprite_bounds(&draw, sprite_screen_x, sprite_height, sprite_width);
	draw.stripe = draw.draw_start_x;
	while (draw.stripe < draw.draw_end_x)
	{
		draw_sprite_pixel(game, &draw, sprite_height, sprite_width);
		draw.stripe++;
	}
}

void	draw_sprite_column_with_zbuffer(t_game *game, t_zbuffer_draw *draw,
									int sprite_height, int sprite_width)
{
	init_zbuffer_bounds(draw, draw->sprite_screen_x, sprite_height,
		sprite_width);
	draw->stripe = draw->draw_start_x;
	while (draw->stripe < draw->draw_end_x)
	{
		if (draw->sprite_distance + 0.1 < game->z_buffer[draw->stripe])
			draw_zbuffer_pixel(game, draw, sprite_height, sprite_width);
		draw->stripe++;
	}
}

void	calculate_sprite_transform(t_game *game, t_npc *npc,
		double *trans_x, double *trans_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = npc->x - game->player.x;
	sprite_y = npc->y - game->player.y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	*trans_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	*trans_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
}
