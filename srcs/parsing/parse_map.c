/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 14:55:44 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/cub3d.h"
#include <stdio.h>

bool is_map_line(char *line)
{
    int i = 0;
    bool has_valid_char = false;

    // Skip leading whitespace
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    // Check if line contains valid map characters
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == '0' || line[i] == '1' || line[i] == 'N' ||
            line[i] == 'S' || line[i] == 'E' || line[i] == 'W' ||
            line[i] == ' ')
        {
            if (line[i] != ' ')
                has_valid_char = true;
        }
        else
            return (false);
        i++;
    }

    // Line must contain at least one valid map character (not just spaces)
    return (has_valid_char);
}

static void find_player_position(char **map, int height, int width, t_vector2d *pos, char *direction)
{
    int y, x;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (map[y][x] == 'N' || map[y][x] == 'S' ||
                map[y][x] == 'E' || map[y][x] == 'W')
            {
                pos->x = x + 0.5;
                pos->y = y + 0.5;
                *direction = map[y][x];
                map[y][x] = '0'; // Replace player with floor
                return;
            }
        }
    }
    error_exit("No player position found in map");
}

static void set_player_direction(t_player *player, char direction)
{
    switch (direction)
    {
        case 'N':
            player->direction.x = 0.0;
            player->direction.y = -1.0;
            player->camera_plane.x = 0.66;
            player->camera_plane.y = 0.0;
            break;
        case 'S':
            player->direction.x = 0.0;
            player->direction.y = 1.0;
            player->camera_plane.x = -0.66;
            player->camera_plane.y = 0.0;
            break;
        case 'E':
            player->direction.x = 1.0;
            player->direction.y = 0.0;
            player->camera_plane.x = 0.0;
            player->camera_plane.y = 0.66;
            break;
        case 'W':
            player->direction.x = -1.0;
            player->direction.y = 0.0;
            player->camera_plane.x = 0.0;
            player->camera_plane.y = -0.66;
            break;
        default:
            error_exit("Invalid player direction");
    }
}

static void validate_map(char **map, int height, int width)
{
    int y, x;

    // Check if map is surrounded by walls
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (map[y][x] == '0')
            {
                // Check if this floor tile is adjacent to empty space
                if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                    error_exit("Map not surrounded by walls");
                if (map[y-1][x] == ' ' || map[y+1][x] == ' ' ||
                    map[y][x-1] == ' ' || map[y][x+1] == ' ')
                    error_exit("Map not surrounded by walls");
            }
        }
    }
}

void parse_map_line(char *line, t_parsing *parsing)
{
    static char **map_lines = NULL;
    static int line_count = 0;
    static int max_width = 0;
    char *clean_line;
    char **new_map_lines;
    int i;

    // Remove only trailing whitespace and newline, preserve leading spaces
    i = ft_strlen(line) - 1;
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r'))
        i--;
    line[i + 1] = '\0';

    // Count characters (width) - include leading spaces
    i = 0;
    while (line[i])
        i++;
    if (i > max_width)
        max_width = i;

    // Add line to map_lines with proper memory management
    new_map_lines = realloc(map_lines, (line_count + 1) * sizeof(char *));
    if (!new_map_lines)
    {
        // Free existing lines if realloc fails
        if (map_lines)
        {
            for (i = 0; i < line_count; i++)
                free(map_lines[i]);
            free(map_lines);
        }
        error_exit("Memory allocation failed");
    }
    map_lines = new_map_lines;

    clean_line = ft_strdup(line);
    if (!clean_line)
    {
        // Free existing lines if strdup fails
        for (i = 0; i < line_count; i++)
            free(map_lines[i]);
        free(map_lines);
        error_exit("Memory allocation failed");
    }

    map_lines[line_count] = clean_line;
    line_count++;

    // Store map data in parsing structure
    parsing->map_lines = map_lines;
    parsing->map_height = line_count;
    parsing->map_width = max_width;
}

char **build_final_map(t_parsing *parsing, t_player *player)
{
    char **map;
    int y, x;
    char player_direction;

    if (!parsing->map_lines || parsing->map_height <= 0 || parsing->map_width <= 0)
        error_exit("No map data found");

    // Allocate final map
    map = malloc(parsing->map_height * sizeof(char *));
    if (!map)
        error_exit("Memory allocation failed");

    for (y = 0; y < parsing->map_height; y++)
    {
        map[y] = malloc(parsing->map_width + 1);
        if (!map[y])
            error_exit("Memory allocation failed");

        // Copy line and pad with spaces if needed
        for (x = 0; x < parsing->map_width; x++)
        {
            if (x < (int)ft_strlen(parsing->map_lines[y]))
                map[y][x] = parsing->map_lines[y][x];
            else
                map[y][x] = ' ';
        }
        map[y][parsing->map_width] = '\0';
    }

    // Find player position and set direction
    find_player_position(map, parsing->map_height, parsing->map_width,
                        &player->position, &player_direction);
    set_player_direction(player, player_direction);

    // Validate map
    validate_map(map, parsing->map_height, parsing->map_width);

    printf("✅ Map loaded: %dx%d, player at (%.1f, %.1f) facing %c\n",
           parsing->map_width, parsing->map_height,
           player->position.x, player->position.y, player_direction);

    return (map);
}
