/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:22:12 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 16:11:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef enum e_parse_state
{
    PARSING_TEXTURES,
    PARSING_MAP
} t_parse_state;

// 🧪 Prototype pour test data
bool parse_test_data(t_game *game);

bool parse_file(t_game *game, char *filename)
{
    int fd;
    char buffer;
    int bytes_read;
    
    printf("📄 Starting to parse: %s\n", filename);
    
    // 🔍 Open file
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("❌ Cannot open file: %s\n", filename);
        return (false);
    }
    
    // 📖 Just read one byte to test file access
    bytes_read = read(fd, &buffer, 1);
    if (bytes_read <= 0)
    {
        printf("❌ Cannot read file: %s\n", filename);
        close(fd);
        return (false);
    }
    
    close(fd);
    
    // 🧪 For now, use test data
    printf("🧪 Using hardcoded test data for now...\n");
    return (parse_test_data(game));
}

// 🧪 Données de test pour valider la structure
bool parse_test_data(t_game *game)
{
    int i;
    
    printf("🧪 Loading test data...\n");
    
    // 🗺️ Map simple 5x5
    game->map.width = 5;
    game->map.height = 5;
    game->map.grid = malloc(sizeof(char*) * 5);
    
    if (!game->map.grid)
    {
        printf("❌ Failed to allocate map grid\n");
        return (false);
    }
    
    // 🗺️ Create simple test map
    game->map.grid[0] = ft_strdup("11111");
    game->map.grid[1] = ft_strdup("10001");
    game->map.grid[2] = ft_strdup("100N1");  // N = player facing North
    game->map.grid[3] = ft_strdup("10001");
    game->map.grid[4] = ft_strdup("11111");
    
    // 🔍 Verify all strings were allocated
    i = 0;
    while (i < game->map.height)
    {
        if (!game->map.grid[i])
        {
            printf("❌ Failed to allocate map line %d\n", i);
            return (false);
        }
        i++;
    }
    
    // 🎮 Player position (center of the room)
    game->player.position.x = 3.5;
    game->player.position.y = 2.5;
    game->player.direction.x = 0.0;
    game->player.direction.y = -1.0;  // Facing North
    
    // 🎨 Simple colors
    game->textures.floor_color = 0x8B4513;    // Brown
    game->textures.ceiling_color = 0x87CEEB;  // Sky blue
    
    printf("✅ Test data loaded successfully:\n");
    printf("   🗺️  Map: %dx%d\n", game->map.width, game->map.height);
    printf("   🎮 Player: (%.1f, %.1f) facing North\n", 
           game->player.position.x, game->player.position.y);
    printf("   🎨 Floor: 0x%X, Ceiling: 0x%X\n", 
           game->textures.floor_color, game->textures.ceiling_color);
    
    // 🧪 Debug: print the map
    printf("   📋 Map layout:\n");
    i = 0;
    while (i < game->map.height)
    {
        printf("      %s\n", game->map.grid[i]);
        i++;
    }
    
    return (true);
}