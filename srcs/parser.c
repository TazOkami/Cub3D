
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:22:12 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/06 XX:XX:XX by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// int	open_cub_file(char *filename)
// {
// 	int	fd;

// 	if (!filename || !ft_strstr(filename, ".cub"))
// 	{
// 		printf("Error: File must have .cub extension\n");
// 		return (-1);
// 	}
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening .cub file");
// 		return (-1);
// 	}
// 	printf("✅ File %s opened successfully\n", filename);
// 	return (fd);
// }

void	init_parsing(t_parsing *parsing)
{
	ft_memset(parsing, 0, sizeof(t_parsing));
	parsing->floor_color[0] = -1;
	parsing->ceiling_color[0] = -1;
}

int	parse_config_only(char *filename, t_parsing *parsing)
{
	int		fd;
	char	*line;

	init_parsing(parsing);
	fd = open_cub_file(filename);
	if (fd < 0)
		return (1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_empty_line(line))
		{
			if (is_texture_line(line))
				parse_texture_line(line, parsing);
			else if (is_color_line(line))
				parse_color_line(line, parsing);
		}
		free(line);
	}
	close(fd);
	return (0);
}

int	setup_map_data(char *filename, t_parsing *parsing)
{
	int	map_line_count;
	int	max_width;

	map_line_count = count_map_lines_and_width(filename, &max_width);
	if (map_line_count <= 0)
	{
		printf("Error: No map data found or file error\n");
		return (1);
	}
	parsing->map_lines = allocate_map_array(map_line_count);
	if (!parsing->map_lines)
	{
		printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (fill_map_from_file(filename, parsing->map_lines, map_line_count))
	{
		printf("Error: Failed to fill map from file\n");
		return (1);
	}
	parsing->map_height = map_line_count;
	parsing->map_width = max_width;
	return (0);
}

int	parse_cub_file(char *filename, t_parsing *parsing)
{
	if (parse_config_only(filename, parsing))
		return (1);
	if (setup_map_data(filename, parsing))
		return (1);
	return (check_parsing_complete(parsing));
}

void	setup_game_colors(t_game *game, t_parsing *parsing)
{
	game->textures.floor_color = (parsing->floor_color[0] << 16)
		| (parsing->floor_color[1] << 8) | parsing->floor_color[2];
	game->textures.ceiling_color = (parsing->ceiling_color[0] << 16)
		| (parsing->ceiling_color[1] << 8) | parsing->ceiling_color[2];
}
int	load_map(char *filename, t_game *game)
{
	t_parsing	parsing;

	printf("🗺️ Loading map from: %s\n", filename);

	// Initialiser la structure de parsing AVANT de l'utiliser
	ft_memset(&parsing, 0, sizeof(t_parsing));

	if (parse_cub_file(filename, &parsing))
	{
		printf("Error: Failed to parse .cub file\n");
		free_parsing_data(&parsing);
		return (1);
	}
	game->map.grid = build_final_map(&parsing, &game->player);
	if (!game->map.grid)
	{
		printf("Error: Failed to build final map\n");
		free_parsing_data(&parsing);
		return (1);
	}
	game->map.width = parsing.map_width;
	game->map.height = parsing.map_height;
	setup_game_colors(game, &parsing);
	transfer_texture_paths(game, &parsing);
	free_parsing_data(&parsing);
	printf("✅ Map loaded successfully!\n");
	return (0);
}