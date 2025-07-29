/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:26:42 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/24 16:45:34 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

void	draw_sprite_pixel(t_game *game, t_sprite_draw *draw,
							int sprite_height, int sprite_width)
{
	int	d;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(256 * (draw->stripe - (-sprite_width / 2 + draw->sprite_screen_x)) * game->sprite[0].width / sprite_width) / 256;
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
	int	d;
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(256 * (draw->stripe - (-sprite_width / 2 
				+ draw->sprite_screen_x)) * game->sprite[draw->anim_frame].width
			/ sprite_width) / 256;
	if (tex_x < 0 || tex_x >= game->sprite[draw->anim_frame].width)
		return ;
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
			if ((color & 0x00FFFFFF) != 0x00FF00FF  && (color & 0x00FFFFFF) != 0x00000000)
				put_pixel_to_img(game, draw->stripe, draw->y, color);
		}
		draw->y++;
	}
}

static void	draw_single_npc(t_game *game, t_npc *npc)
{
	double			transform_x;
	double			transform_y;
	double			sprite_distance;
	t_zbuffer_draw	draw;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;

	sprite_distance = sqrt((npc->x - game->player.x) * (npc->x - game->player.x)
			+ (npc->y - game->player.y) * (npc->y - game->player.y));
	calculate_sprite_transform(game, npc, &transform_x, &transform_y);
	if (transform_y > 0 && sprite_distance > 0.1)
	{
		sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
		sprite_height = abs((int)(HEIGHT / transform_y * 0.7));
		sprite_width = sprite_height;
		if (sprite_screen_x > -sprite_width  && sprite_screen_x < WIDTH + sprite_width)
		{
			draw.sprite_screen_x = sprite_screen_x;
			draw.sprite_distance = transform_y;
			draw.anim_frame = npc->anim_frame;
			draw_sprite_column_with_zbuffer(game, &draw, sprite_height,
				sprite_width);
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
