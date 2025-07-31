/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 16:33:52 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	is_texture_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (true);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (true);
	return (false);
}

static char	*extract_path(char *line)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (NULL);
	i = ft_strlen(path) - 1;
	while (i >= 0 && (path[i] == ' ' || path[i] == '\t'
			|| path[i] == '\n' || path[i] == '\r'))
	{
		path[i] = '\0';
		i--;
	}
	return (path);
}

static void	set_texture(char **texture_ptr, char *path, char *error_msg)
{
	if (*texture_ptr)
		error_exit(error_msg);
	*texture_ptr = path;
}

void	parse_texture_line(char *line, t_parsing *parsing)
{
	char	*path;

	path = extract_path(line);
	if (!path)
		error_exit("Failed to extract texture path");
	if (ft_strncmp(line, "NO ", 3) == 0)
		set_texture(&parsing->north_texture, path,
			"North texture already defined");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		set_texture(&parsing->south_texture, path,
			"South texture already defined");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		set_texture(&parsing->west_texture, path,
			"West texture already defined");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		set_texture(&parsing->east_texture, path,
			"East texture already defined");
}
