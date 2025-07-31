/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:28:53 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 14:28:53 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_ray_step_and_side_distances(t_ray *ray, t_game *game)
{
	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_distance.x = (game->player.position.x - ray->map_position.x)
			* ray->delta_distance.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_distance.x = (ray->map_position.x
				+ 1.0 - game->player.position.x) * ray->delta_distance.x;
	}
	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_distance.y = (game->player.position.y
				- ray->map_position.y) * ray->delta_distance.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_distance.y = (ray->map_position.y
				+ 1.0 - game->player.position.y) * ray->delta_distance.y;
	}
}

static void	init_ray_delta_distances(t_ray *ray)
{
	if (ray->direction.x == 0)
		ray->delta_distance.x = 1e30;
	else
		ray->delta_distance.x = fabs(1 / ray->direction.x);
	if (ray->direction.y == 0)
		ray->delta_distance.y = 1e30;
	else
		ray->delta_distance.y = fabs(1 / ray->direction.y);
}

void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->direction.x = game->player.direction.x
		+ game->player.camera_plane.x * camera_x;
	ray->direction.y = game->player.direction.y
		+ game->player.camera_plane.y * camera_x;
	ray->map_position.x = (int)game->player.position.x;
	ray->map_position.y = (int)game->player.position.y;
	init_ray_delta_distances(ray);
	init_ray_step_and_side_distances(ray, game);
}

void	cast_single_ray(t_game *game, int x)
{
	t_ray	ray;

	init_ray(&ray, game, x);
	perform_dda(&ray, game);
	calculate_wall_distance(&ray, game);
	draw_wall_column(game, &ray, x);
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		cast_single_ray(game, x);
		x++;
	}
}
