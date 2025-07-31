#include "../../includes/cub3d.h"

void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->direction.x = game->player.direction.x + game->player.camera_plane.x
						* camera_x;
	ray->direction.y = game->player.direction.y + game->player.camera_plane.y
						* camera_x;

	ray->map_position.x = (int)game->player.position.x;
	ray->map_position.y = (int)game->player.position.y;

	if (ray->direction.x == 0)
		ray->delta_distance.x = 1e30;
	else
		ray->delta_distance.x = fabs(1 / ray->direction.x);

	if (ray->direction.y == 0)
		ray->delta_distance.y = 1e30;
	else
		ray->delta_distance.y = fabs(1 / ray->direction.y);

	if (ray->direction.x < 0)
	{
		ray->step.x = -1;
		ray->side_distance.x = (game->player.position.x - ray->map_position.x)
								* ray->delta_distance.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_distance.x = (ray->map_position.x + 1.0 - game->player.position.x)
								* ray->delta_distance.x;
	}

	if (ray->direction.y < 0)
	{
		ray->step.y = -1;
		ray->side_distance.y = (game->player.position.y - ray->map_position.y)
								* ray->delta_distance.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_distance.y = (ray->map_position.y + 1.0 - game->player.position.y)
								* ray->delta_distance.y;
	}
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

		if (get_map_cell(game, ray->map_position.x, ray->map_position.y) == WALL)
			ray->wall_hit = true;
	}
}

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

	// Select texture based on wall side
	if (ray->hit_side == 0) // North/South walls
	{
		if (ray->step.x > 0) // South wall
			texture = &game->textures.south_wall;
		else // North wall
			texture = &game->textures.north_wall;
	}
	else // East/West walls
	{
		if (ray->step.y > 0) // East wall
			texture = &game->textures.east_wall;
		else // West wall
			texture = &game->textures.west_wall;
	}

	// Calculate wall_x (exact position where ray hit the wall)
	if (ray->hit_side == 0)
		wall_x = game->player.position.y + ray->perpendicular_wall_distance * ray->direction.y;
	else
		wall_x = game->player.position.x + ray->perpendicular_wall_distance * ray->direction.x;
	wall_x -= floor(wall_x);

	// Calculate texture_x coordinate
	texture_x = (int)(wall_x * texture->width);
	if (ray->hit_side == 0 && ray->direction.x > 0)
		texture_x = texture->width - texture_x - 1;
	if (ray->hit_side == 1 && ray->direction.y < 0)
		texture_x = texture->width - texture_x - 1;

	// Calculate step and starting position for texture
	step = 1.0 * texture->height / line_height;
	texture_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

	// Draw the wall column
	y = draw_start;
	while (y < draw_end)
	{
		int texture_y = (int)texture_pos & (texture->height - 1);
		texture_pos += step;

		// Get pixel from texture
		color = get_texture_pixel(texture, texture_x, texture_y);

		// Apply distance shading
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
