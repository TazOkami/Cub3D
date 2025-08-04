/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:38:20 by malafont          #+#    #+#             */
/*   Updated: 2025/08/04 15:38:22 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

bool	is_map_line(char *line)
{
	int		i;
	bool	has_valid_char;

	has_valid_char = false;
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == ' ')
		{
			if (line[i] != ' ')
				has_valid_char = true;
		}
		else
			return (false);
		i++;
	}
	return (has_valid_char);
}

bool	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_from_map(t_vector2d *pos, char *dir,
	t_map_pos pos_data)
{
	pos->x = pos_data.x + 0.5;
	pos->y = pos_data.y + 0.5;
	*dir = pos_data.grid[pos_data.y][pos_data.x];
	pos_data.grid[pos_data.y][pos_data.x] = '0';
}

void	find_player_position(t_temp_map map,
	t_vector2d *pos, char *dir)
{
	int			y;
	int			x;
	t_map_pos	pd;

	pd.grid = map.grid;
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width)
		{
			if (is_spawn(map.grid[y][x]))
			{
				pd.y = y;
				pd.x = x;
				set_player_from_map(pos, dir, pd);
				return ;
			}
			x++;
		}
		y++;
	}
	error_exit("No player position found in map");
}

void	validate_map(char **map, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '0')
			{
				if (y == 0 || y == height - 1
					|| x == 0 || x == width - 1)
					error_exit("Map not surrounded by walls");
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
					|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					error_exit("Map not surrounded by walls");
			}
			x++;
		}
		y++;
	}
}
