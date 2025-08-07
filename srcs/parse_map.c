/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/06 XX:XX:XX by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	process_map_line_count(char *line, int *count, int *max_width)
{
	int	len;

	if (is_map_line(line))
	{
		len = clean_line_length(line);
		if (len > *max_width)
			*max_width = len;
		(*count)++;
	}
}

int	count_map_lines_and_width(char *filename, int *max_width)
{
	int		fd;
	char	*line;
	int		count;

	fd = open_cub_file(filename);
	if (fd < 0)
		return (-1);
	count = 0;
	*max_width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_map_line_count(line, &count, max_width);
		free(line);
	}
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	clean_line_length(char *line)
{
	int	len;

	len = ft_strlen(line);
	len--;
	while (len >= 0 && (line[len] == ' ' || line[len] == '\t'
			|| line[len] == '\n' || line[len] == '\r'))
		len--;
	return (len + 1);
}

char	**allocate_map_array(int line_count)
{
	char	**map_lines;
	int		i;

	map_lines = malloc(sizeof(char *) * line_count);
	if (!map_lines)
		return (NULL);
	i = 0;
	while (i < line_count)
	{
		map_lines[i] = NULL;
		i++;
	}
	return (map_lines);
}

void	clean_and_copy_line(char *dst, char *src)
{
	int	len;
	int	i;

	len = clean_line_length(src);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = '\0';
}
