/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-18 10:56:30 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-18 10:56:30 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	gun_fire(t_game *g)
{
	int i;
	
	i = 0;

	g->gun.img = mlx_xpm_file_to_image(g->mlx, g->gun.tex_fire_1,
			&g->gun.tex_width, &g->gun.tex_height);
	g->gun.tex_data = mlx_get_data_addr(g->gun.img, &g->gun.tex_bpp,
			&g->gun.tex_size_line, &g->gun.tex_endian);
	draw_gun(g);
	while (i < 500000)
		i++;
	g->gun.img = mlx_xpm_file_to_image(g->mlx, g->gun.tex_fire_2,
			&g->gun.tex_width, &g->gun.tex_height);
	g->gun.tex_data = mlx_get_data_addr(g->gun.img, &g->gun.tex_bpp,
			&g->gun.tex_size_line, &g->gun.tex_endian);
	draw_gun(g);
	i = 0;
	while (i < 500000)
		i++;
	g->gun.img = mlx_xpm_file_to_image(g->mlx, g->gun.tex_repos,
			&g->gun.tex_width, &g->gun.tex_height);
	g->gun.tex_data = mlx_get_data_addr(g->gun.img, &g->gun.tex_bpp,
			&g->gun.tex_size_line, &g->gun.tex_endian);
	draw_gun(g);
}
