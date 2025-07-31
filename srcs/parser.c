/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:22:12 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 14:28:46 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <fcntl.h>

static bool is_empty_line(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
            return (false);
        i++;
    }
    return (true);
}

int open_cub_file(char *filename)
{
	int fd;

	if (!ft_strstr(filename, ".cub"))
	{
		printf("Error: File must have .cub extension\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening .cub file");
		return (-1);
	}
	printf("✅ File %s opened successfully\n", filename);
	return (fd);
}

int parse_cub_file(char *filename, t_parsing *parsing)
{
	int fd;
	char *line;

	fd = open_cub_file(filename);
	if (fd < 0)
		return (1);

	// Initialize parsing structure
	ft_memset(parsing, 0, sizeof(t_parsing));
	parsing->floor_color[0] = -1;
	parsing->ceiling_color[0] = -1;

	while ((line = get_next_line(fd)) != NULL)
    {
		if (is_empty_line(line))
        {
            free(line);
            continue;
        }
        else if (is_texture_line(line))
        	parse_texture_line(line, parsing);
    	else if (is_color_line(line))
        	parse_color_line(line, parsing);
    	else if (is_map_line(line))
        	parse_map_line(line, parsing);
		else
			error_exit("Invalid line in .cub file");
        free(line);
    }
    close(fd);
    return (check_parsing_complete(parsing));
}

int check_parsing_complete(t_parsing *parsing)
{
    if (!parsing->north_texture)
        error_exit("North texture not defined");
    if (!parsing->south_texture)
        error_exit("South texture not defined");
    if (!parsing->west_texture)
        error_exit("West texture not defined");
    if (!parsing->east_texture)
        error_exit("East texture not defined");
    if (parsing->floor_color[0] == -1)
        error_exit("Floor color not defined");
    if (parsing->ceiling_color[0] == -1)
        error_exit("Ceiling color not defined");
    if (!parsing->map_lines || parsing->map_height <= 0)
        error_exit("No map data found");

    parsing->all_loaded = true;
    printf("✅ All parsing elements completed successfully\n");
    return (0);
}

int load_map(char *filename, t_game *game)
{
    t_parsing parsing;

    printf("🗺️ Loading map from: %s\n", filename);

    if (parse_cub_file(filename, &parsing))
    {
        free_parsing_data(&parsing);
        cleanup_and_exit(game, "Failed to parse .cub file");
    }

    // Build final map and set player position
    game->map.grid = build_final_map(&parsing, &game->player);
    game->map.width = parsing.map_width;
    game->map.height = parsing.map_height;

    // Set colors
    game->textures.floor_color = (parsing.floor_color[0] << 16) |
                                 (parsing.floor_color[1] << 8) |
                                 parsing.floor_color[2];
    game->textures.ceiling_color = (parsing.ceiling_color[0] << 16) |
                                   (parsing.ceiling_color[1] << 8) |
                                   parsing.ceiling_color[2];

    // Store texture paths for later loading
    game->textures.north_path = parsing.north_texture;
    game->textures.south_path = parsing.south_texture;
    game->textures.east_path = parsing.east_texture;
    game->textures.west_path = parsing.west_texture;

    printf("✅ Map loaded successfully!\n");
    return (0);
}
