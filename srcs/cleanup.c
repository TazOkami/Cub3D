/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:37:42 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/05 16:37:15 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_textures(t_game *game)
{
	if (game->textures.north_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.north_wall.image_ptr);
	if (game->textures.south_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.south_wall.image_ptr);
	if (game->textures.east_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.east_wall.image_ptr);
	if (game->textures.west_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.west_wall.image_ptr);
	printf("🧹 Textures freed\n");
}

void	free_parsing_data(t_parsing *parsing)
{
	int	i;

	if (!parsing)
		return ;
	if (parsing->north_texture)
		free(parsing->north_texture);
	if (parsing->south_texture)
		free(parsing->south_texture);
	if (parsing->west_texture)
		free(parsing->west_texture);
	if (parsing->east_texture)
		free(parsing->east_texture);
	if (parsing->map_lines)
	{
		i = 0;
		while (i < parsing->map_height)
		{
			if (parsing->map_lines[i])
				free(parsing->map_lines[i]);
			i++;
		}
		free(parsing->map_lines);
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	if (game->textures.north_path)
		free(game->textures.north_path);
	if (game->textures.south_path)
		free(game->textures.south_path);
	if (game->textures.east_path)
		free(game->textures.east_path);
	if (game->textures.west_path)
		free(game->textures.west_path);
	if (game->mlx.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
	if (game->mlx.window_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
	if (game->map.grid)
		free_map_grid(game->map.grid, game->map.height);
	if (game->sprites)
		free(game->sprites);
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
