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

void	update_gun_animation(t_game	*g)
{
	if (g->gun.fire_timer > 0)
	{
		g->gun.fire_timer--;
		if (g->gun.fire_timer == 0)
		{
			if (g->gun.img)
				mlx_destroy_image(g->mlx, g->gun.img);
			g->gun.img = mlx_xpm_file_to_image(g->mlx, g->gun.tex_repos,
					&g->gun.tex_width, &g->gun.tex_height);
			if (g->gun.img)
				g->gun.tex_data = mlx_get_data_addr(g->gun.img, &g->gun.tex_bpp,
						&g->gun.tex_size_line, &g->gun.tex_endian);
		}
	}
}

/*Make the gun firing*/
void	gun_fire(t_game *g)
{
	g->gun.fire_timer = g->gun.fire_duration;
	if (g->gun.img)
		mlx_destroy_image(g->mlx, g->gun.img);
	g->gun.img = mlx_xpm_file_to_image(g->mlx, g->gun.tex_fire,
			&g->gun.tex_width, &g->gun.tex_height);
	if (g->gun.img)
		g->gun.tex_data = mlx_get_data_addr(g->gun.img, &g->gun.tex_bpp,
				&g->gun.tex_size_line, &g->gun.tex_endian);
}
