/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:25:23 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/05 16:25:37 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_from_map(t_vector2d *pos, char *dir,
	t_map_pos pos_data)
{
	pos->x = pos_data.x + 0.5;
	pos->y = pos_data.y + 0.5;
	*dir = pos_data.grid[pos_data.y][pos_data.x];
	pos_data.grid[pos_data.y][pos_data.x] = '0';
}

static int	count_players(t_temp_map map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = -1;
	while (++y < map.height)
	{
		x = -1;
		while (++x < map.width)
			if (is_spawn(map.grid[y][x]))
				count++;
	}
	if (count == 0)
		error_exit("No player position found in map");
	if (count > 1)
		error_exit("Multiple player positions found in map");
	return (count);
}

void	find_player_position(t_temp_map map, t_vector2d *pos, char *dir)
{
	int			y;
	int			x;
	int			player_count;
	t_map_pos	pd;

	player_count = count_players(map);
	if (player_count == 1)
	{
		pd.grid = map.grid;
		y = -1;
		while (++y < map.height)
		{
			x = -1;
			while (++x < map.width)
			{
				if (is_spawn(map.grid[y][x]))
				{
					pd.y = y;
					pd.x = x;
					set_player_from_map(pos, dir, pd);
					return ;
				}
			}
		}
	}
}
