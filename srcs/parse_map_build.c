
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 XX:XX:XX by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/06 XX:XX:XX by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_temp_map	create_tmp_map(char **map, t_parsing *parsing)
{
	t_temp_map	map_wrapper;

	map_wrapper.grid = map;
	map_wrapper.width = parsing->map_width;
	map_wrapper.height = parsing->map_height;
	return (map_wrapper);
}

char	**build_final_map(t_parsing *parsing, t_player *player)
{
	char		**map;
	int			y;
	char		player_dir;
	t_temp_map	map_wrapper;

	if (!parsing->map_lines || parsing->map_height <= 0
		|| parsing->map_width <= 0)
		error_exit("No map data found");
	map = malloc(sizeof(char *) * parsing->map_height);
	if (!map)
		error_exit("Memory allocation failed");
	y = 0;
	while (y < parsing->map_height)
	{
		map[y] = malloc(parsing->map_width + 1);
		if (!map[y])
			return (free_partial_map(map, y));
		fill_map_row(map[y], parsing->map_lines[y], parsing->map_width);
		y++;
	}
	map_wrapper = create_tmp_map(map, parsing);
	find_player_position(map_wrapper, &player->position, &player_dir);
	set_player_direction(player, player_dir);
	validate_map(map, parsing->map_height, parsing->map_width);
	return (map);
}
