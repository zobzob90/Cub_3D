/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 14:56:16 by vdeliere          #+#    #+#             */
/*   Updated: 2025/07/22 14:11:14 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Initialise the parameters of one ray for the x column*/
static void	init_ray_vars(t_game *g, t_ray *r, int x)
{
	r->camera_x = 2 * x / (double)WIDTH - 1;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	r->hit = 0;
}

/*Calculate the direction and the distance until the next grid intersection*/
static void	init_step_and_side(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->player.y) * r->delta_dist_y;
	}
}

/*Calculate the perpendicular distance to the wall
	in order to avoid the fish-eye effect*/
static void	calculate_distance(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->player.x + (1 - r->step_x) / 2.0)
			/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player.y + (1 - r->step_y) / 2.0)
			/ r->ray_dir_y;
	if (r->side == 0)
		r->wall_x = g->player.y + r->perp_wall_dist * r->ray_dir_y;
	else
		r->wall_x = g->player.x + r->perp_wall_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)TEX_WIDTH);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->tex_x < 0)
		r->tex_x = 0;
	if (r->tex_x >= TEX_WIDTH)
		r->tex_x = TEX_WIDTH - 1;
}

/*Throw a complete ray for a x column*/
static void	cast_single_ray(t_game *g, int x)
{
	t_ray			ray;
	int				line_height;
	int				start;
	int				end;
	t_draw_params	params;

	init_ray_vars(g, &ray, x);
	init_step_and_side(g, &ray);
	perform_dda(g, &ray);
	calculate_distance(g, &ray);
	if (ray.perp_wall_dist > 0)
		line_height = (int)(HEIGHT / ray.perp_wall_dist);
	else
		line_height = HEIGHT;
	start = -line_height / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	params.x = x;
	params.start = start;
	params.end = end;
	params.ray = &ray;
	draw_textured_line(g, &params);
}

/*Main function of the raycasting. Draw the scene*/
void	draw_scene(t_game *g)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		cast_single_ray(g, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	draw_gun(g);
	if (g->show_minimap)
		draw_mini_map(g);
}
