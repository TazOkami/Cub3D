/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:19:36 by malafont          #+#    #+#             */
/*   Updated: 2025/08/07 13:20:52 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_map(char *filename, t_game *game)
{
	t_parsing	parsing;

	printf("🗺️ Loading map from: %s\n", filename);
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
