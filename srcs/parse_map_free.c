/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:38:03 by malafont          #+#    #+#             */
/*   Updated: 2025/08/04 15:38:05 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

int	free_and_return(char **map_lines, int count, char *line, int fd)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (map_lines[i])
			free(map_lines[i]);
		i++;
	}
	free(map_lines);
	free(line);
	close(fd);
	return (1);
}

char	**free_partial_map(char **map, int allocated_count)
{
	int	i;

	i = 0;
	while (i < allocated_count)
	{
		free(map[i]);
		i++;
	}
	free(map);
	error_exit("Memory allocation failed");
	return (NULL);
}

void	clean_gnl_buffer(int fd)
{
	char	*line;

	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}
