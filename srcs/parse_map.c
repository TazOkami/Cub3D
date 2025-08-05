/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/05 17:41:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_line_copy(char *line, char **map_lines,
	int count, t_parsing *parsing)
{
	char	*clean;

	clean = ft_strdup(line);
	if (!clean)
	{
		free_map_lines(map_lines, count);
		error_exit("Memory allocation failed");
	}
	map_lines[count] = clean;
	parsing->map_lines = map_lines;
	parsing->map_height = count + 1;
}

void	parse_map_line(char *line, t_parsing *parsing)
{
	static char	**map_lines;
	static int	count;
	static int	max_width;
	char		**new_lines;
	int			i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\n' || line[i] == '\r'))
		i--;
	line[i + 1] = '\0';
	i = ft_strlen(line);
	if (i > max_width)
		max_width = i;
	new_lines = realloc(map_lines, sizeof(char *) * (count + 1));
	if (!new_lines)
	{
		if (map_lines)
			free_map_lines(map_lines, count);
		error_exit("Memory allocation failed");
	}
	map_lines = new_lines;
	handle_line_copy(line, map_lines, count, parsing);
	parsing->map_width = max_width;
	count++;
}

static void	fill_map_row(char *dst, char *src, int width)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(src);
	while (x < width)
	{
		if (x < len)
			dst[x] = src[x];
		else
			dst[x] = ' ';
		x++;
	}
	dst[width] = '\0';
}

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
			error_exit("Memory allocation failed");
		fill_map_row(map[y], parsing->map_lines[y], parsing->map_width);
		y++;
	}
	map_wrapper = create_tmp_map(map, parsing);
	find_player_position(map_wrapper, &player->position, &player_dir);
	set_player_direction(player, player_dir);
	validate_map(map, parsing->map_height, parsing->map_width);
	return (map);
}
