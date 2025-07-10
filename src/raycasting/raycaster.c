/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdeliere <vdeliere@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-09 14:56:16 by vdeliere          #+#    #+#             */
/*   Updated: 2025-07-09 14:56:16 by vdeliere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_game *g, int x, double *camera_x, double *ray_dir_x, double *ray_dir_y)
{
	*camera_x = 2 * x / (double)WIDTH - 1;
	*ray_dir_x = g->player.dir_x + g->player.plane_x * (*camera_x);
	*ray_dir_y = g->player.dir_y + g->player.plane_y * (*camera_x);
}

static void	init_step(t_game *g, double ray_dir_x, double ray_dir_y,
	double *s_dist_x, double *s_dist_y)
{

}

static void	perform_dda(t_game *g, int *map_x, int *map_y,
	double *s_dist_x, double *s_dist_y)
{

}

static double	get_wall_distance(t_game *g, int map_x, int map_y,
	double ray_dir_x, double ray_dir_y)
{

}

void	draw_scene(t_game *g)
{

}