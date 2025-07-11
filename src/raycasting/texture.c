/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-10 16:00:00 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-10 16:00:00 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *g)
{
	g->tex_north = mlx_xpm_file_to_image(g->mlx, "texture/xpm/wall_north.xpm", 
		&g->tex_width, &g->tex_height);
	g->tex_south = mlx_xpm_file_to_image(g->mlx, "texture/xpm/wall_south.xpm", 
		&g->tex_width, &g->tex_height);
	g->tex_east = mlx_xpm_file_to_image(g->mlx, "texture/xpm/wall_east.xpm", 
		&g->tex_width, &g->tex_height);
	g->tex_west = mlx_xpm_file_to_image(g->mlx, "texture/xpm/wall_west.xpm", 
		&g->tex_width, &g->tex_height);
	if (!g->tex_north)
		g->tex_north = mlx_new_image(g->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!g->tex_south)
		g->tex_south = mlx_new_image(g->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!g->tex_east)
		g->tex_east = mlx_new_image(g->mlx, TEX_WIDTH, TEX_HEIGHT);
	if (!g->tex_west)
		g->tex_west = mlx_new_image(g->mlx, TEX_WIDTH, TEX_HEIGHT);
	g->tex_north_data = mlx_get_data_addr(g->tex_north, &g->tex_bpp, 
		&g->tex_size_line, &g->tex_endian);
	g->tex_south_data = mlx_get_data_addr(g->tex_south, &g->tex_bpp, 
		&g->tex_size_line, &g->tex_endian);
	g->tex_east_data = mlx_get_data_addr(g->tex_east, &g->tex_bpp, 
		&g->tex_size_line, &g->tex_endian);
	g->tex_west_data = mlx_get_data_addr(g->tex_west, &g->tex_bpp, 
		&g->tex_size_line, &g->tex_endian);
}

int	get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y)
{
	char	*tex_data;
	char	*pixel;

	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT)
		return (0x000000);
	if (tex_num == 0)
		tex_data = game->tex_north_data;
	else if (tex_num == 1)
		tex_data = game->tex_south_data;
	else if (tex_num == 2)
		tex_data = game->tex_east_data;
	else
		tex_data = game->tex_west_data;
	pixel = tex_data + (tex_y * game->tex_size_line + tex_x * (game->tex_bpp / 8));
	return (*(unsigned int*)pixel);
}
