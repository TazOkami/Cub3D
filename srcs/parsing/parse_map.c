/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/24 17:35:21 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse_map(char *filename, t_game *game)
{
    printf("Parsing file: %s\n", filename);
    
    // Pour l'instant, créons une map simple en dur
    game->map.width = 24;
    game->map.height = 13;
    
    // Position initiale du joueur
    game->player.x = 12.0;
    game->player.y = 6.0;
    game->player.angle = 0.0;
    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
    
    printf("Map parsed successfully!\n");
    return (0);
}