/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:34:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/27 15:34:10 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
typedef struct s_textures
{
    t_image wall;
    t_image floor; 
    t_image player;
    t_image collectible;
    t_image exit;
    // Plus tard: ennemis, animations...
} t_textures;

typedef struct s_image
{
    void    *img_ptr;
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
} t_image;
