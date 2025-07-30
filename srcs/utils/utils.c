/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:08:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 08:55:14 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;

	offset = y * game->mlx.line_length + x * (game->mlx.bits_per_pixel / 8);
	dst = game->mlx.image_data + offset;
	*(unsigned int*)dst = color;
}

int	is_wall_at(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;

	if (map_x < 0 || map_x >= game->map.width || map_y < 0 || map_y >= game->map.height)
		return (1);

	return (get_map_cell(game, map_x, map_y) == WALL);
}

int	get_map_cell(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (WALL);

	if (!game->map.grid || !game->map.grid[y])
		return (WALL);

	return (game->map.grid[y][x] - '0');
}

void	free_map_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;

	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

void	error_exit(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	cleanup_resources(t_game *game)
{
	if (game->mlx.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
	if (game->mlx.window_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_display(game->mlx.mlx_ptr);
	if (game->mlx.mlx_ptr)
		free(game->mlx.mlx_ptr);
	if (game->map.grid)
		free_map_grid(game->map.grid, game->map.height);
	if (game->sprites)
		free(game->sprites);
}
