/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:21:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 19:07:10 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool init_player(t_player *player)
{
	player->position.x = WIN_WIDTH / 2.0;
	player->position.y = WIN_HEIGHT / 2.0;
	player->direction.x = -1.0;
	player->direction.y = 0.0;
	player->camera_plane.x = 0.0;
	player->camera_plane.y = 0.66;  // FOV ~66°
	player->move_speed = 0.05;
	player->rotation_speed = 0.03;
	printf("🎮 Player initialized at (%.0f, %.0f) facing West\n", 
		   player->position.x, player->position.y);
	return (true);
}

bool	init_game(t_game *game)
{
	// Zero everything
	memset(game, 0, sizeof(t_game));
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
