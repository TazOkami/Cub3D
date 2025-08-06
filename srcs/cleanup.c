
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:37:42 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/06 XX:XX:XX by Jpaulis          ###   ########.fr       */
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

void	free_texture_paths(t_game *game)
{
	if (game->textures.north_path)
	{
		free(game->textures.north_path);
		game->textures.north_path = NULL;
	}
	if (game->textures.south_path)
	{
		free(game->textures.south_path);
		game->textures.south_path = NULL;
	}
	if (game->textures.east_path)
	{
		free(game->textures.east_path);
		game->textures.east_path = NULL;
	}
	if (game->textures.west_path)
	{
		free(game->textures.west_path);
		game->textures.west_path = NULL;
	}
}

void	free_mlx_resources(t_game *game)
{
	if (game->mlx.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
	if (game->mlx.window_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}
}

void	transfer_texture_paths(t_game *game, t_parsing *parsing)
{
	game->textures.north_path = parsing->north_texture;
	game->textures.south_path = parsing->south_texture;
	game->textures.east_path = parsing->east_texture;
	game->textures.west_path = parsing->west_texture;
	parsing->north_texture = NULL;
	parsing->south_texture = NULL;
	parsing->east_texture = NULL;
	parsing->west_texture = NULL;
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	free_textures(game);
	free_texture_paths(game);
	free_mlx_resources(game);
	if (game->map.grid)
		free_map_grid(game->map.grid, game->map.height);
	if (game->sprites)
		free(game->sprites);
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