/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:34:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 17:16:05 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool init_textures(t_game *game)
{
    printf("🖼️ Loading textures...\n");
    
    // Charger chaque texture
    if (!load_texture(&game->mlx, &game->textures.wall, "textures/wall.xpm"))
        return (false);
    if (!load_texture(&game->mlx, &game->textures.floor, "textures/floor.xpm"))
        return (false);
    if (!load_texture(&game->mlx, &game->textures.player, "textures/player.xpm"))
        return (false);
    if (!load_texture(&game->mlx, &game->textures.collectible, "textures/collectible.xpm"))
        return (false);
    if (!load_texture(&game->mlx, &game->textures.exit, "textures/exit.xpm"))
        return (false);
        
    printf("✅ All textures loaded!\n");
    return (true);
}
