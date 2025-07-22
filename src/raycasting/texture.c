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

static void	error_texture_path(t_game *g)
{
	ft_putstr_fd("Error\nInvalid texture path\n", 2);
	close_win(g);
}

/*Load all the .xpm textures*/
void	load_textures(t_game *g)
{
	g->tex_north = mlx_xpm_file_to_image(g->mlx, g->map->texture.no,
			&g->tex_width, &g->tex_height);
	g->tex_south = mlx_xpm_file_to_image(g->mlx, g->map->texture.so,
			&g->tex_width, &g->tex_height);
	g->tex_east = mlx_xpm_file_to_image(g->mlx, g->map->texture.ea,
			&g->tex_width, &g->tex_height);
	g->tex_west = mlx_xpm_file_to_image(g->mlx, g->map->texture.we,
			&g->tex_width, &g->tex_height);
	g->gun.img = mlx_xpm_file_to_image(g->mlx, g->gun.tex_repos,
			&g->gun.tex_width, &g->gun.tex_height);
	if (!g->tex_north || !g->tex_south || !g->tex_east
		|| !g->tex_west || !g->gun.img)
		error_texture_path(g);
	g->tex_north_data = mlx_get_data_addr(g->tex_north, &g->tex_bpp,
			&g->tex_size_line, &g->tex_endian);
	g->tex_south_data = mlx_get_data_addr(g->tex_south, &g->tex_bpp,
			&g->tex_size_line, &g->tex_endian);
	g->tex_east_data = mlx_get_data_addr(g->tex_east, &g->tex_bpp,
			&g->tex_size_line, &g->tex_endian);
	g->tex_west_data = mlx_get_data_addr(g->tex_west, &g->tex_bpp,
			&g->tex_size_line, &g->tex_endian);
	g->gun.tex_data = mlx_get_data_addr(g->gun.img, &g->gun.tex_bpp,
			&g->gun.tex_size_line, &g->gun.tex_endian);
}

/*Get the color of one pixel(tex_x, tex_y) in the texture*/
int	get_texture_pixel(t_game *game, int tex_num, int tex_x, int tex_y)
{
	char	*tex_data;
	char	*pixel;

	if (tex_x < 0 || tex_x >= TEX_WIDTH || tex_y < 0 || tex_y >= TEX_HEIGHT)
		return (0x666666);
	if (tex_num == 0)
		tex_data = game->tex_north_data;
	else if (tex_num == 1)
		tex_data = game->tex_south_data;
	else if (tex_num == 2)
		tex_data = game->tex_east_data;
	else if (tex_num == 3)
		tex_data = game->tex_west_data;
	else
		return (0x666666);
	if (!tex_data)
		return (0x666666);
	pixel = tex_data + (tex_y * game->tex_size_line
			+ tex_x * (game->tex_bpp / 8));
	return (*(unsigned int *)pixel);
}
