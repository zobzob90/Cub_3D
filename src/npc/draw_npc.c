/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:26:42 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/30 15:03:31 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_sprite_pixel(t_game *game, t_sprite_draw *draw,
	int sprite_height, int sprite_width)
{
	int	d;
	int	tex_x;
	int	tex_y;
	int	color;
	int	temp_calc;

	temp_calc = draw->stripe - (-sprite_width / 2 + draw->sprite_screen_x);
	tex_x = (int)(256 * temp_calc * game->sprite[0].width / sprite_width) / 256;
	if (tex_x < 0 || tex_x >= game->sprite[0].width)
		return ;
	draw->y = draw->draw_start_y;
	while (draw->y < draw->draw_end_y)
	{
		d = draw->y * 256 - HEIGHT * 128 + sprite_height * 128;
		tex_y = ((d * game->sprite[0].height) / sprite_height) / 256;
		if (tex_y >= 0 && tex_y < game->sprite[0].height)
		{
			color = get_pixel_from_sprite(&game->sprite[0], tex_x, tex_y);
			if (color != 0xFF00FF && color != 0x000000
				&& (color & 0xFF000000) != 0)
				put_pixel_to_img(game, draw->stripe, draw->y, color);
		}
		draw->y++;
	}
}

void	init_zbuffer_bounds(t_zbuffer_draw *draw, int sprite_screen_x,
							int sprite_height, int sprite_width)
{
	draw->sprite_screen_x = sprite_screen_x;
	draw->draw_start_y = -sprite_height / 2 + HEIGHT / 2 + sprite_height / 8;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = sprite_height / 2 + HEIGHT / 2 + sprite_height / 8;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
	draw->draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}

void	draw_zbuffer_pixel(t_game *game, t_zbuffer_draw *draw,
	int sprite_height, int sprite_width)
{
	int	tex_x;
	int	temp_calc;

	temp_calc = draw->stripe - (-sprite_width / 2 + draw->sprite_screen_x);
	tex_x = (int)(256 * temp_calc * game->sprite[draw->anim_frame].width
			/ sprite_width) / 256;
	if (tex_x < 0 || tex_x >= game->sprite[draw->anim_frame].width)
		return ;
	render_zbuffer_column(game, draw, sprite_height, tex_x);
}

static void	draw_single_npc(t_game *game, t_npc *npc)
{
	double			transform_x;
	double			transform_y;
	t_zbuffer_draw	draw;
	int				sprite_screen_x;
	int				sprite_size;

	calculate_sprite_transform(game, npc, &transform_x, &transform_y);
	if (transform_y > 0 && calculate_sprite_distance(npc, &game->player) > 0.1)
	{
		sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
		sprite_size = abs((int)(HEIGHT / transform_y * 0.7));
		if (sprite_screen_x > -sprite_size
			&& sprite_screen_x < WIDTH + sprite_size)
		{
			setup_sprite_draw(&draw, npc, sprite_screen_x, transform_y);
			draw_sprite_column_with_zbuffer(game, &draw, sprite_size,
				sprite_size);
		}
	}
}

void	draw_npcs_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map->num_npcs)
	{
		draw_single_npc(game, &game->map->npcs[i]);
		i++;
	}
}
