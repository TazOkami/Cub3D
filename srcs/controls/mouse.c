/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:42:53 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 15:57:58 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int handle_mouse(int x, int y, t_game *game)
// {
//     static int last_x = -1;
    
//     if (last_x == -1)
//     {
//         last_x = x;
//         return (0);
//     }
    
//     // 🎯 Rotation basée sur déplacement souris
//     int delta_x = x - last_x;
//     double rotation = delta_x * MOUSE_SENSITIVITY;
    
//     if (abs(delta_x) > 2) // 🎯 Seuil pour éviter micro-mouvements
//     {
//         rotate_right(game, rotation);
        
//         // 🎯 Recentrer souris pour rotation continue
//         if (x < 100 || x > WIN_WIDTH - 100)
//         {
//             mlx_mouse_move(game->mlx.mlx_ptr, game->mlx.win_ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
//             last_x = WIN_WIDTH / 2;
//         }
//         else
//             last_x = x;
//     }
    
//     return (0);
// }