/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 12:51:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_map_line(char *line)
{
    int i = 0;
    
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
            line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
            line[i] != ' ')
            return (false);
        i++;
    }
    return (true);
}

static bool is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
            c == 'E' || c == 'W' || c == ' ');
}

static bool is_player_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool contains_map_content(char *line)
{
    int i;
    bool has_map_content;
    
    if (!line)
        return (false);
    
    i = 0;
    has_map_content = false;
    
    // Skip leading spaces
    while (line[i] && line[i] == ' ')
        i++;
    
    // Vérifie si la ligne contient des caractères de map
    while (line[i])
    {
        if (!is_valid_map_char(line[i]))
            return (false);
        if (line[i] != ' ')
            has_map_content = true;
        i++;
    }
    
    return (has_map_content);
}

void parse_map_line(char *line, t_parsing *parsing)
{
    // Variables static pour stocker la map temporairement
    static char **map_lines = NULL;
    static int map_height = 0;
    static int map_width = 0;
    static bool player_found = false;
    static int player_x = 0;
    static int player_y = 0;
    static char player_dir = 0;
    static bool map_started = false;
    
    if (!line || !parsing)
        return;
    
    // Vérifie si c'est une ligne de map valide
    if (!contains_map_content(line))
    {
        // Si on avait commencé la map, c'est fini
        if (map_started && map_height > 0)
        {
            printf("🏁 Map parsing completed!\n");
            printf("📊 Map: %d lines, max width: %d\n", map_height, map_width);
            
            if (player_found)
                printf("👤 Player '%c' at position (%d, %d)\n", 
                       player_dir, player_x, player_y);
            else
                printf("❌ Warning: No player found in map!\n");
            
            // TODO: Ici tu pourrais transférer vers une structure t_game plus tard
        }
        return;
    }
    
    // Début de la map
    if (!map_started)
    {
        printf("🗺️ Starting map parsing...\n");
        map_started = true;
        map_height = 0;
        map_width = 0;
        player_found = false;
    }
    
    // Réalloque le tableau de lignes
    char **new_map = realloc(map_lines, sizeof(char *) * (map_height + 1));
    if (!new_map)
    {
        printf("❌ Error: Memory allocation failed for map line\n");
        return;
    }
    map_lines = new_map;
    
    // Duplique la ligne
    map_lines[map_height] = ft_strdup(line);
    if (!map_lines[map_height])
    {
        printf("❌ Error: Failed to duplicate map line\n");
        return;
    }
    
    // Met à jour la largeur max
    int line_len = ft_strlen(line);
    if (line_len > map_width)
        map_width = line_len;
    
    // Cherche le joueur dans cette ligne
    int x = 0;
    while (line[x])
    {
        if (is_player_char(line[x]))
        {
            if (player_found)
            {
                printf("❌ Error: Multiple players found in map!\n");
                return;
            }
            player_found = true;
            player_x = x;
            player_y = map_height;
            player_dir = line[x];
            printf("👤 Player '%c' found at position (%d, %d)\n", 
                   player_dir, player_x, player_y);
        }
        x++;
    }
    
    map_height++;
    printf("📏 Added map line %d (length: %d)\n", map_height, line_len);
    
    // Marque que le parsing continue (pas fini)
    (void)parsing; // évite le warning unused
}

