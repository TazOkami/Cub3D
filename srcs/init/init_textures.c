/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:34:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 12:53:16 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool load_texture(t_mlx_context *mlx, t_texture *texture, char *path)
{
    int bits_per_pixel;
    int line_length;
    int endian;
    
    if (!mlx || !mlx->mlx_ptr || !texture || !path)
    {
        printf("❌ Error: Invalid parameters for texture loading\n");
        return (false);
    }
    
    // Charger l'image avec MLX
    texture->image_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, 
                                               &texture->width, &texture->height);
    if (!texture->image_ptr)
    {
        printf("❌ Error: Could not load texture '%s'\n", path);
        return (false);
    }
    
    // Récupérer les données de pixels
    texture->pixels = (unsigned int *)mlx_get_data_addr(texture->image_ptr,
                                                        &bits_per_pixel,
                                                        &line_length,
                                                        &endian);
    if (!texture->pixels)
    {
        printf("❌ Error: Could not get pixel data for '%s'\n", path);
        mlx_destroy_image(mlx->mlx_ptr, texture->image_ptr);
        return (false);
    }
    
    printf("✅ Loaded texture: %s (%dx%d)\n", path, texture->width, texture->height);
    return (true);
}

static int rgb_to_int(int rgb[3])
{
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

bool init_textures(t_game *game)
{
    if (!game)
    {
        printf("❌ Error: Game structure is NULL\n");
        return (false);
    }
    
    if (!game->parsing.all_loaded)
    {
        printf("❌ Error: Parsing not completed before texture initialization\n");
        return (false);
    }
    
    printf("🖼️ Loading textures...\n");
    
    // Charger les textures des murs
    if (!load_texture(&game->mlx, &game->textures.north_wall, game->parsing.north_texture))
        return (false);
        
    if (!load_texture(&game->mlx, &game->textures.south_wall, game->parsing.south_texture))
        return (false);
        
    if (!load_texture(&game->mlx, &game->textures.west_wall, game->parsing.west_texture))
        return (false);
        
    if (!load_texture(&game->mlx, &game->textures.east_wall, game->parsing.east_texture))
        return (false);
    
    // Convertir les couleurs RGB en entiers
    game->textures.floor_color = rgb_to_int(game->parsing.floor_color);
    game->textures.ceiling_color = rgb_to_int(game->parsing.ceiling_color);
    
    printf("🎨 Floor color: RGB(%d,%d,%d) -> 0x%06X\n", 
           game->parsing.floor_color[0], game->parsing.floor_color[1], 
           game->parsing.floor_color[2], game->textures.floor_color);
           
    printf("🎨 Ceiling color: RGB(%d,%d,%d) -> 0x%06X\n", 
           game->parsing.ceiling_color[0], game->parsing.ceiling_color[1], 
           game->parsing.ceiling_color[2], game->textures.ceiling_color);
    
    printf("✅ All textures and colors loaded successfully!\n");
    return (true);
}
