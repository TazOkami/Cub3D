#include "../includes/cub3d.h"

int	fill_map_from_file(char *filename, char **map_lines, int expected_count)
{
	int		fd;
	char	*line;
	int		map_index;

	fd = open_cub_file(filename);
	if (fd < 0)
		return (1);
	map_index = 0;
	while (map_index < expected_count)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map_line(line))
		{
			map_lines[map_index] = ft_strdup(line);
			if (!map_lines[map_index])
				return (free_and_return(map_lines, map_index, line, fd));
			clean_and_copy_line(map_lines[map_index], line);
			map_index++;
		}
		free(line);
	}
	close(fd);
	return (0);
}

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

void	fill_map_row(char *dst, char *src, int width)
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

int	open_cub_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening .cub file");
		return (-1);
	}
	printf("✅ File %s opened successfully\n", filename);
	return (fd);
}