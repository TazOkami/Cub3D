/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:41:46 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 16:43:20 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_parsing_complete(t_parsing *parsing)
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

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\r')
			return (false);
		i++;
	}
	return (true);
}
