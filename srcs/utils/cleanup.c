/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:00:00 by malafont         #+#    #+#             */
/*   Updated: 2025/07/30 15:00:00 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/cub3d.h"

void	free_parsing_data(t_parsing *parsing)
{
	int i;

	if (!parsing)
		return;

	// Free texture paths
	if (parsing->north_texture)
		free(parsing->north_texture);
	if (parsing->south_texture)
		free(parsing->south_texture);
	if (parsing->west_texture)
		free(parsing->west_texture);
	if (parsing->east_texture)
		free(parsing->east_texture);

	// Free map lines
	if (parsing->map_lines)
	{
		for (i = 0; i < parsing->map_height; i++)
		{
			if (parsing->map_lines[i])
				free(parsing->map_lines[i]);
		}
		free(parsing->map_lines);
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return;

	// Free textures
	free_textures(game);

	// Free texture paths
	if (game->textures.north_path)
		free(game->textures.north_path);
	if (game->textures.south_path)
		free(game->textures.south_path);
	if (game->textures.east_path)
		free(game->textures.east_path);
	if (game->textures.west_path)
		free(game->textures.west_path);

	// Free MLX resources
	if (game->mlx.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
	if (game->mlx.window_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	if (game->mlx.mlx_ptr)
	{
		mlx_destroy_display(game->mlx.mlx_ptr);
		free(game->mlx.mlx_ptr);
	}

	// Free map
	if (game->map.grid)
		free_map_grid(game->map.grid, game->map.height);

	// Free sprites
	if (game->sprites)
		free(game->sprites);
}