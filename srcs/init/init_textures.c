/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/25 19:24:31 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map_struct(t_map *map)
{
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    map->no_texture = NULL;
    map->so_texture = NULL; 
    map->we_texture = NULL;
    map->ea_texture = NULL;
    map->floor_color[0] = -1;   // -1 = pas encore parsé
    map->floor_color[1] = -1;
    map->floor_color[2] = -1;
    map->ceiling_color[0] = -1;
    map->ceiling_color[1] = -1;
    map->ceiling_color[2] = -1;
}