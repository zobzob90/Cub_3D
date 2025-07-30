/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:45:00 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 14:45:00 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_sprite_distance(t_npc *npc, t_player *player)
{
	double	dx;
	double	dy;

	dx = npc->x - player->x;
	dy = npc->y - player->y;
	return (sqrt(dx * dx + dy * dy));
}

void	setup_sprite_draw(t_zbuffer_draw *draw, t_npc *npc,
	int sprite_screen_x, double transform_y)
{
	draw->sprite_screen_x = sprite_screen_x;
	draw->sprite_distance = transform_y;
	draw->anim_frame = npc->anim_frame;
}

void	render_zbuffer_column(t_game *game, t_zbuffer_draw *draw,
	int sprite_height, int tex_x)
{
	int	d;
	int	tex_y;
	int	color;

	draw->y = draw->draw_start_y;
	while (draw->y < draw->draw_end_y)
	{
		d = draw->y * 256 - HEIGHT * 128 + sprite_height * 128;
		tex_y = ((d * game->sprite[draw->anim_frame].height)
				/ sprite_height) / 256;
		if (tex_y >= 0 && tex_y < game->sprite[draw->anim_frame].height)
		{
			color = get_pixel_from_sprite(&game->sprite[draw->anim_frame],
					tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0x00FF00FF
				&& (color & 0x00FFFFFF) != 0x00000000)
				put_pixel_to_img(game, draw->stripe, draw->y, color);
		}
		draw->y++;
	}
}

void	init_sprite_bounds(t_sprite_draw *draw, int sprite_screen_x,
	int sprite_height, int sprite_width)
{
	draw->sprite_screen_x = sprite_screen_x;
	draw->draw_start_y = -sprite_height / 2 + HEIGHT / 2;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = sprite_height / 2 + HEIGHT / 2;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
	draw->draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}
