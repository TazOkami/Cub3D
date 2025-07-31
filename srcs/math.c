/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:02:10 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 17:04:31 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_distance(t_ray *ray, t_game *game)
{
	(void)game;
	if (ray->hit_side == 0)
		ray->perpendicular_wall_distance = (ray->side_distance.x
				- ray->delta_distance.x);
	else
		ray->perpendicular_wall_distance = (ray->side_distance.y
				- ray->delta_distance.y);
}

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->wall_hit = false;
	while (!ray->wall_hit)
	{
		if (ray->side_distance.x < ray->side_distance.y)
		{
			ray->side_distance.x += ray->delta_distance.x;
			ray->map_position.x += ray->step.x;
			ray->hit_side = 0;
		}
		else
		{
			ray->side_distance.y += ray->delta_distance.y;
			ray->map_position.y += ray->step.y;
			ray->hit_side = 1;
		}
		if (get_map_cell(game, ray->map_position.x,
				ray->map_position.y) == WALL)
			ray->wall_hit = true;
	}
}
