/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:07:45 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/24 17:42:04 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (-1);
    
    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    if (!game->win)
        return (-1);
    
    game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!game->img.img)
        return (-1);
    
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
                                       &game->img.line_length, &game->img.endian);
    
	  // Hooks pour les événements
    mlx_key_hook(game->win, key_press, game);
    mlx_hook(game->win, 17, 0, close_window, game); // Bouton X
    
    // Premier rendu
    render_frame(game);
    
    // Boucle MLX
    mlx_loop(game->mlx);
    return (0);
}