/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 12:44:38 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Dans srcs/parsing/transfer_data.c ou srcs/init/transfer_data.c
bool transfer_parsed_data(t_game *game)
{
    // Transfert des textures parsed vers game->textures
    // (pour l'instant, juste validation)
    
    if (!game->parsing.all_loaded)
    {
        printf("❌ Parsing not complete\n");
        return (false);
    }
    
    // Conversion des couleurs parsing -> textures si nécessaire
    game->textures.floor_color = 
        (game->parsing.floor_color[0] << 16) |
        (game->parsing.floor_color[1] << 8) |
        game->parsing.floor_color[2];
        
    game->textures.ceiling_color = 
        (game->parsing.ceiling_color[0] << 16) |
        (game->parsing.ceiling_color[1] << 8) |
        game->parsing.ceiling_color[2];
    
    // Pour l'instant, valeurs temporaires pour la map
    game->map.width = 10;   // À remplacer par les vraies valeurs
    game->map.height = 10;  // À remplacer par les vraies valeurs
    
    printf("✅ Data transferred from parsing to game structure\n");
    return (true);
}


int main(int argc, char **argv)
{
    t_game game;
    
    // ✅ 1. Vérification des arguments
    if (argc != 2)
    {
        printf("Usage: ./cub3D map.cub\n");
        return (1);
    }
    
    // ✅ 2. Initialiser la structure de jeu
    if (!init_game(&game))
        error_exit("Failed to initialize game");
    
    // ✅ 3. Parser le fichier .cub
    if (!parse_cub_file(argv[1], &game.parsing))
        error_exit("Failed to parse map file");
    
    // ✅ 4. Transférer les données parsées
    if (!transfer_parsed_data(&game))
        error_exit("Failed to transfer parsed data");
    
    // ✅ 5. Initialiser MLX
    if (!init_mlx(&game))
        error_exit("MLX init failed");
    
    // ✅ 6. Charger tes textures (TON CODE EXISTANT)
    if (!init_textures(&game))
        error_exit("Textures init failed");
    
    // ✅ 7. Configurer les événements
    if (!init_events(&game))
        error_exit("Events init failed");
    
    // ✅ 8. Affichage debug
    printf("✅ Game initialized successfully!\n");
    printf("📊 Map size: %dx%d\n", game.map.width, game.map.height);
    printf("🎮 Player at: (%.2f, %.2f)\n", game.player.position.x, game.player.position.y);
    printf("🎨 Floor color: RGB(%d,%d,%d)\n", 
           game.parsing.floor_color[0], 
           game.parsing.floor_color[1], 
           game.parsing.floor_color[2]);
    printf("🎨 Ceiling color: RGB(%d,%d,%d)\n", 
           game.parsing.ceiling_color[0], 
           game.parsing.ceiling_color[1], 
           game.parsing.ceiling_color[2]);
    printf("🚀 Starting game loop...\n");
    
    // ✅ 9. Lancer la boucle de jeu
    mlx_loop(game.mlx.mlx_ptr);
    
    // ✅ 10. Nettoyage
    cleanup_game(&game);
    
    printf("👋 Game closed properly!\n");
    return (0);
}



// int main(int argc, char **argv)
// {
// 	t_game game;
// 	int fd;
//     char *line;
	
// 	if (argc != 2)
// 	{
// 		printf("Usage: ./cub3D map.cub\n");
// 		return (1);
// 	}
// 	fd = open_cub_file(argv[1]);
//     if (fd == -1)
//         return (1);
    
//     // Test 2 : Lire ligne par ligne
//     printf("📖 Reading file content:\n");
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("Line: %s", line);
//         free(line);
//     }
// 	if (!init_game(&game))
// 		error_exit("Failed to initialize game");
// 	if (!parse_cub_file(argv[1], &game.parsing))
// 		error_exit("Failed to parse map file");
// 	if (!init_mlx(&game))
//         return (error_exit("MLX init failed"));
//     // if (!init_textures(&game))
//     //     return (error_exit("Textures init failed"));
//     if (!init_events(&game))
//     {
//         error_exit("Events init failed");
//         return (1);
//     }
// 	printf("✅ Game initialized successfully!\n");
// 	printf("📊 Map size: %dx%d\n", game.map.width, game.map.height);
// 	printf("🎮 Player at: (%.2f, %.2f)\n", game.player.position.x, game.player.position.y);
// 	mlx_loop(game.mlx.mlx_ptr);
// 	cleanup_game(&game);
// 	close(fd);
// 	printf("✅ File read successfully!\n");
// 	return (0);
// }
