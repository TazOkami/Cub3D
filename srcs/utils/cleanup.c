/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:14:01 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 17:29:36 by Jpaulis          ###   ########.fr       */
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
	if (game->mlx.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
	if (game->mlx.window_ptr && !game->mlx.window_destroyed)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	printf("🧹 Game cleaned up\n");
}

int close_window(t_game *game)
{
    printf("🚪 Closing window...\n");
    game->game_running = false;
    exit(0);
    return (0);
}