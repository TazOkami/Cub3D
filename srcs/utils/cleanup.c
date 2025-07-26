/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:14:01 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 18:50:33 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cleanup_game(t_game *game)
{
	int i;
	
	// Free map
	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	// Free MLX (si initialisé)
	if (game->mlx.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
	if (game->mlx.window_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	printf("🧹 Game cleaned up\n");
}