/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:00:47 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 17:03:21 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_and_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				put_pixel(game, x, y, game->textures.ceiling_color);
			else
				put_pixel(game, x, y, game->textures.floor_color);
			x++;
		}
		y++;
	}
}

void	render_scene(t_game *game)
{
	draw_floor_and_ceiling(game);
	cast_rays(game);
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		y;
	t_texture	*texture;
	double	wall_x;
	int		texture_x;
	double	step;
	double	texture_pos;

	line_height = (int)(SCREEN_HEIGHT / ray->perpendicular_wall_distance);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	if (ray->hit_side == 0)
	{
		if (ray->step.x > 0)
			texture = &game->textures.south_wall;
		else
			texture = &game->textures.north_wall;
	}
	else
	{
		if (ray->step.y > 0)
			texture = &game->textures.east_wall;
		else
			texture = &game->textures.west_wall;
	}
	if (ray->hit_side == 0)
		wall_x = game->player.position.y + ray->perpendicular_wall_distance * ray->direction.y;
	else
		wall_x = game->player.position.x + ray->perpendicular_wall_distance * ray->direction.x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * texture->width);
	if (ray->hit_side == 0 && ray->direction.x > 0)
		texture_x = texture->width - texture_x - 1;
	if (ray->hit_side == 1 && ray->direction.y < 0)
		texture_x = texture->width - texture_x - 1;
	step = 1.0 * texture->height / line_height;
	texture_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		int texture_y = (int)texture_pos & (texture->height - 1);
		texture_pos += step;
		color = get_texture_pixel(texture, texture_x, texture_y);
		double distance_factor = 1.0 / (1.0 + ray->perpendicular_wall_distance * 0.1);
		int r = (color >> 16) & 0xFF;
		int g = (color >> 8) & 0xFF;
		int b = color & 0xFF;
		r = (int)(r * distance_factor);
		g = (int)(g * distance_factor);
		b = (int)(b * distance_factor);
		color = (r << 16) | (g << 8) | b;
		put_pixel(game, x, y, color);
		y++;
	}
}
