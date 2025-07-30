/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:21:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 11:07:41 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/cub3d.h"
#include <stdio.h>
int	init_default_map(t_game *game)
{
	char	*map_data[MAP_HEIGHT];
	int		i;

	// Map par défaut (8x8) avec plus de murs
	map_data[0] = "1111111111111111";
	map_data[1] = "1000000000000001";
	map_data[2] = "1000000000000001";
	map_data[3] = "1000100000000001";
	map_data[4] = "1000000000001001";
	map_data[5] = "1011100000000001";
	map_data[6] = "1000000000000001";
	map_data[7] = "1000000000000001";
	map_data[8] = "1000100000000001";
	map_data[9] = "1000000000001001";
	map_data[10] = "1011100000000001";
	map_data[11] = "1000000000000001";
	map_data[12] = "1111111111111111";

	game->map.grid = malloc(sizeof(char *) * MAP_HEIGHT);
	if (!game->map.grid)
		return (1);

	i = 0;
	while (i < MAP_HEIGHT)
	{
		game->map.grid[i] = ft_strdup(map_data[i]);
		if (!game->map.grid[i])
		{
			free_map_grid(game->map.grid, i);
			return (1);
		}
		i++;
	}

	game->map.width = MAP_WIDTH;
	game->map.height = MAP_HEIGHT;
	game->map.sprite_count = 0;
	game->sprites = NULL;

	return (0);
}

static bool init_player(t_player *player)
{
	player->position.x = 1.5;
	player->position.y = 1.5;
	player->direction.x = -1.0;
	player->direction.y = 0.0;
	player->camera_plane.x = 0.0;
	player->camera_plane.y = 0.66;  // FOV ~66°
	player->move_speed = 0.5;
	player->rotation_speed = 0.3;
	printf("🎮 Player initialized at (%.1f, %.1f) facing West\n",
		   player->position.x, player->position.y);
	return (true);
}

bool	init_game(t_game *game)
{
	// Zero everything
	ft_memset(game, 0, sizeof(t_game));
	if (!init_player(&game->player))
	{
		printf("❌ Player initialization failed\n");
		return (false);
	}
	// Init map
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	// Init colors to invalid values
	game->textures.floor_color = -1;
	game->textures.ceiling_color = -1;
	// Game state
	game->game_running = true;
	printf("✅ Game structure initialized\n");
	return (true);
}
