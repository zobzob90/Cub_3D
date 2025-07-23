/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:26:42 by ertrigna          #+#    #+#             */
/*   Updated: 2025/07/23 17:34:45 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_pixel_from_sprite(t_sprite *sprite, int x, int y)
{
    int	color;
    int	index;

    if (x < 0 || x >= sprite->width || y < 0 || y >= sprite->height)
        return (0);
    
    index = (y * sprite->size_line + x * (sprite->bpp / 8));
    color = *(unsigned int*)(sprite->img_data + index);
    return (color);
}

void	draw_sprite_column(t_game *game, int sprite_screen_x, int sprite_height, int sprite_width)
{
    int	draw_start_y;
    int	draw_end_y;
    int	draw_start_x;
    int	draw_end_x;
    int	stripe;
    int	y;
    int	d;
    int	tex_x;
    int	tex_y;
    int	color;

    draw_start_y = -sprite_height / 2 + HEIGHT / 2;
    if (draw_start_y < 0)
        draw_start_y = 0;
    draw_end_y = sprite_height / 2 + HEIGHT / 2;
    if (draw_end_y >= HEIGHT)
        draw_end_y = HEIGHT - 1;
    draw_start_x = -sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0)
        draw_start_x = 0;
    draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_end_x >= WIDTH)
        draw_end_x = WIDTH - 1;
    stripe = draw_start_x;
    while (stripe < draw_end_x)
    {
        tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * game->sprite[0].width / sprite_width) / 256;
        if (tex_x < 0 || tex_x >= game->sprite[0].width)
        {
            stripe++;
            continue;
        }
        y = draw_start_y;
        while (y < draw_end_y)
        {
            d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
            tex_y = ((d * game->sprite[0].height) / sprite_height) / 256;
            if (tex_y >= 0 && tex_y < game->sprite[0].height)
            {
                color = get_pixel_from_sprite(&game->sprite[0], tex_x, tex_y);
                if (color != 0xFF00FF && color != 0x000000 && (color & 0xFF000000) != 0)
                    put_pixel_to_img(game, stripe, y, color);
            }
            y++;
        }
        stripe++;
    }
}

void	draw_sprite_column_with_zbuffer(t_game *game, int sprite_screen_x, int sprite_height, int sprite_width, double sprite_distance, int anim_frame)
{
	int	draw_start_y;
	int	draw_end_y;
	int	draw_start_x;
	int	draw_end_x;
	int	stripe;
	int	y;
	int	d;
	int	tex_x;
	int	tex_y;
	int	color;

	draw_start_y = -sprite_height / 2 + HEIGHT / 2 + sprite_height / 8; // Léger décalage vers le bas
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + HEIGHT / 2 + sprite_height / 8; // Léger décalage vers le bas
	if (draw_end_y >= HEIGHT)
        draw_end_y = HEIGHT - 1;
    draw_start_x = -sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0)
        draw_start_x = 0;
    draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_end_x >= WIDTH)
        draw_end_x = WIDTH - 1;
    stripe = draw_start_x;
    while (stripe < draw_end_x)
    {
        if (sprite_distance + 0.1 < game->z_buffer[stripe])
        {
            tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * game->sprite[anim_frame].width / sprite_width) / 256;
            if (tex_x >= 0 && tex_x < game->sprite[anim_frame].width)
            {
                y = draw_start_y;
                while (y < draw_end_y)
                {
                    d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
                    tex_y = ((d * game->sprite[anim_frame].height) / sprite_height) / 256;
                    if (tex_y >= 0 && tex_y < game->sprite[anim_frame].height)
                    {
                        color = get_pixel_from_sprite(&game->sprite[anim_frame], tex_x, tex_y);
                        if ((color & 0x00FFFFFF) != 0x00FF00FF && (color & 0x00FFFFFF) != 0x00000000)
                            put_pixel_to_img(game, stripe, y, color);
                    }
                    y++;
                }
            }
        }
        stripe++;
    }
}

void	draw_npcs_sprites(t_game *game)
{
    int	i;
    
    i = 0;
    while (i < game->map->num_npcs)
    {
        t_npc *npc = &game->map->npcs[i];
        
        double sprite_x = npc->x - game->player.x;
        double sprite_y = npc->y - game->player.y;
        double sprite_distance = sqrt(sprite_x * sprite_x + sprite_y * sprite_y);
        double inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - 
                                game->player.dir_x * game->player.plane_y);
        double transform_x = inv_det * (game->player.dir_y * sprite_x - 
                                        game->player.dir_x * sprite_y);
        double transform_y = inv_det * (-game->player.plane_y * sprite_x + 
                                        game->player.plane_x * sprite_y);
        if (transform_y > 0 && sprite_distance > 0.1)
        {
            int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
            double scale_factor = 0.7;
            int sprite_height = abs((int)(HEIGHT / transform_y * scale_factor));
            int sprite_width = sprite_height;
            if (sprite_screen_x > -sprite_width && sprite_screen_x < WIDTH + sprite_width)
            {
                draw_sprite_column_with_zbuffer(game, sprite_screen_x, sprite_height, sprite_width, transform_y, npc->anim_frame);
            }
        }
        i++;
    }
}

int	is_transparent_pixel(int color)
{
	unsigned char alpha;
	
	alpha = (color >> 24) & 0xFF;
	if (alpha == 0)
		return (1);
	if ((color & 0x00FFFFFF) == 0x00FF00FF)
		return (1);
	return (0);
}
