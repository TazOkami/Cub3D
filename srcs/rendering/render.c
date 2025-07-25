/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/24 17:39:16 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_background(t_game *game)
{
    int x, y;
    
    // Ciel (bleu clair)
    for (y = 0; y < WINDOW_HEIGHT / 2; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            put_pixel(&game->img, x, y, 0x87CEEB); // Sky blue
        }
    }
    
    // Sol (vert)
    for (y = WINDOW_HEIGHT / 2; y < WINDOW_HEIGHT; y++)
    {
        for (x = 0; x < WINDOW_WIDTH; x++)
        {
            put_pixel(&game->img, x, y, 0x228B22); // Forest green
        }
    }
}

void draw_crosshair(t_game *game)
{
    int center_x = WINDOW_WIDTH / 2;
    int center_y = WINDOW_HEIGHT / 2;
    int size = 10;
    
    // Ligne horizontale
    for (int i = -size; i <= size; i++)
        put_pixel(&game->img, center_x + i, center_y, 0xFFFFFF);
    
    // Ligne verticale
    for (int i = -size; i <= size; i++)
        put_pixel(&game->img, center_x, center_y + i, 0xFFFFFF);
}

void render_frame(t_game *game)
{
    // Dessiner le background
    draw_background(game);
    
    // Dessiner un viseur
    draw_crosshair(game);
    
    // Afficher l'image dans la fenêtre
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
