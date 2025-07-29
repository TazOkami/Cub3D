/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 18:22:07 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game game;
	int fd;
    char *line;
	
	if (argc != 2)
	{
		printf("Usage: ./cub3D map.cub\n");
		return (1);
	}
	fd = open_cub_file(argv[1]);
    if (fd == -1)
        return (1);
    
    // Test 2 : Lire ligne par ligne
    printf("📖 Reading file content:\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
	if (!init_game(&game))
		error_exit("Failed to initialize game");
	if (!parse_cub_file(argv[1], &game.parsing))
		error_exit("Failed to parse map file");
	if (!init_mlx(&game))
        return (error_exit("MLX init failed"));
    // if (!init_textures(&game))
    //     return (error_exit("Textures init failed"));
    if (!init_events(&game))
    {
        error_exit("Events init failed");
        return (1);
    }
	printf("✅ Game initialized successfully!\n");
	printf("📊 Map size: %dx%d\n", game.map.width, game.map.height);
	printf("🎮 Player at: (%.2f, %.2f)\n", game.player.position.x, game.player.position.y);
	mlx_loop(game.mlx.mlx_ptr);
	cleanup_game(&game);
	close(fd);
	printf("✅ File read successfully!\n");
	return (0);
}
