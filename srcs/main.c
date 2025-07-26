/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 19:12:43 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game game;
	
	if (argc != 2)
	{
		printf("Usage: ./cub3D map.cub\n");
		return (1);
	}
	if (!init_game(&game))
		error_exit("Failed to initialize game");
	if (!parse_file(&game, argv[1]))
		error_exit("Failed to parse map file");
	if (!init_mlx(&game))
        return (error_exit("MLX init failed"));
    // if (!init_textures(&game))
    //     return (error_exit("Textures init failed"));
    // if (!init_events(&game))
    //     return (error_exit("Events init failed"));
	printf("✅ Game initialized successfully!\n");
	printf("📊 Map size: %dx%d\n", game.map.width, game.map.height);
	printf("🎮 Player at: (%.2f, %.2f)\n", game.player.position.x, game.player.position.y);
	mlx_loop(game.mlx.mlx_ptr);
	cleanup_game(&game);
	return (0);
}
