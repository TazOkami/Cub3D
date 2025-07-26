/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:21:20 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 16:05:26 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool init_mlx(t_game *game)
{
    // 🖥️ Init MLX
    game->mlx.mlx_ptr = mlx_init();
    if (!game->mlx.mlx_ptr)
        return (false);
    
    // 🪟 Create window
    game->mlx.window_ptr = mlx_new_window(game->mlx.mlx_ptr, 
                                         WIN_WIDTH, WIN_HEIGHT, 
                                         "Cub3D");
    if (!game->mlx.window_ptr)
        return (false);
    
    // 🖼️ Create image buffer
    game->mlx.image_ptr = mlx_new_image(game->mlx.mlx_ptr, 
                                       WIN_WIDTH, WIN_HEIGHT);
    if (!game->mlx.image_ptr)
        return (false);
    
    // 📊 Get image data
    game->mlx.image_data = mlx_get_data_addr(game->mlx.image_ptr,
                                            &game->mlx.bits_per_pixel,
                                            &game->mlx.line_length,
                                            &game->mlx.endian);
    
    printf("✅ MLX initialized successfully\n");
    return (true);
}

