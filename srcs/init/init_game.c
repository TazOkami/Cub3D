/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:21:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 16:14:23 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_game(t_game *game)
{
	// 🧹 Zero everything
	memset(game, 0, sizeof(t_game));
	// 🎮 Init player defaults
	game->player.move_speed = 0.05;
	game->player.rotation_speed = 0.03;
	game->player.camera_plane.x = 0.0;
	game->player.camera_plane.y = 0.66;  // FOV ~66°
	// 🗺️ Init map
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	// 🎨 Init colors to invalid values
	game->textures.floor_color = -1;
	game->textures.ceiling_color = -1;
	// 🎯 Game state
	game->game_running = true;
	printf("✅ Game structure initialized\n");
	return (true);
}
