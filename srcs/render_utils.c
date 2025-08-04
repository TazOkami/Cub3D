/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:39:06 by malafont          #+#    #+#             */
/*   Updated: 2025/08/04 13:39:16 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->hit_side == 0)
	{
		if (ray->step.x > 0)
			return (&game->textures.south_wall);
		return (&game->textures.north_wall);
	}
	if (ray->step.y > 0)
		return (&game->textures.east_wall);
	return (&game->textures.west_wall);
}

int	get_texture_x(t_game *game, t_ray *ray, t_texture *texture)
{
	double	wall_x;
	int		texture_x;

	if (ray->hit_side == 0)
		wall_x = game->player.position.y
			+ ray->perpendicular_wall_distance * ray->direction.y;
	else
		wall_x = game->player.position.x
			+ ray->perpendicular_wall_distance * ray->direction.x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture->width);
	if (ray->hit_side == 0 && ray->direction.x > 0)
		texture_x = texture->width - texture_x - 1;
	if (ray->hit_side == 1 && ray->direction.y < 0)
		texture_x = texture->width - texture_x - 1;
	return (texture_x);
}
