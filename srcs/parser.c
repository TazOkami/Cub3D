/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:22:12 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 16:43:43 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	open_cub_file(char *filename)
{
	int	fd;

	if (!filename || !ft_strstr(filename, ".cub"))
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

static void	init_parsing(t_parsing *parsing)
{
	ft_memset(parsing, 0, sizeof(t_parsing));
	parsing->floor_color[0] = -1;
	parsing->ceiling_color[0] = -1;
}

static void	process_line(char *line, t_parsing *parsing)
{
	if (is_texture_line(line))
		parse_texture_line(line, parsing);
	else if (is_color_line(line))
		parse_color_line(line, parsing);
	else if (is_map_line(line))
		parse_map_line(line, parsing);
	else
		error_exit("Invalid line in .cub file");
}

int	parse_cub_file(char *filename, t_parsing *parsing)
{
	int		fd;
	char	*line;

	fd = open_cub_file(filename);
	if (fd < 0)
		return (1);
	init_parsing(parsing);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_empty_line(line))
			process_line(line, parsing);
		free(line);
	}
	close(fd);
	return (check_parsing_complete(parsing));
}

int	load_map(char *filename, t_game *game)
{
	t_parsing	parsing;

	printf("🗺️ Loading map from: %s\n", filename);
	if (parse_cub_file(filename, &parsing))
	{
		//free_parsing_data(&parsing);
		cleanup_and_exit(game, "Failed to parse .cub file");
	}
	game->map.grid = build_final_map(&parsing, &game->player);
	game->map.width = parsing.map_width;
	game->map.height = parsing.map_height;
	game->textures.floor_color = (parsing.floor_color[0] << 16)
		| (parsing.floor_color[1] << 8) | parsing.floor_color[2];
	game->textures.ceiling_color = (parsing.ceiling_color[0] << 16)
		| (parsing.ceiling_color[1] << 8) | parsing.ceiling_color[2];
	game->textures.north_path = parsing.north_texture;
	game->textures.south_path = parsing.south_texture;
	game->textures.east_path = parsing.east_texture;
	game->textures.west_path = parsing.west_texture;
	printf("✅ Map loaded successfully!\n");
	return (0);
}
