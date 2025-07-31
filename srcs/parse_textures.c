/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 14:28:42 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

bool is_texture_line(char *line)
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

static char *extract_path(char *line)
{
    char *path;
    int i = 0;

    // Skip identifier (NO, SO, WE, EA)
    while (line[i] && line[i] != ' ')
        i++;
    // Skip spaces
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    path = ft_strdup(line + i);
    if (!path)
        return (NULL);

    // Remove trailing whitespace and newline
    i = ft_strlen(path) - 1;
    while (i >= 0 && (path[i] == ' ' || path[i] == '\t' || path[i] == '\n' || path[i] == '\r'))
    {
        path[i] = '\0';
        i--;
    }

    return (path);
}

void parse_texture_line(char *line, t_parsing *parsing)
{
    char *path;

    path = extract_path(line);
    if (!path)
        error_exit("Failed to extract texture path");

    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        if (parsing->north_texture)
            error_exit("North texture already defined");
        parsing->north_texture = path;
        printf("✅ North texture: %s\n", path);
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        if (parsing->south_texture)
            error_exit("South texture already defined");
        parsing->south_texture = path;
        printf("✅ South texture: %s\n", path);
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        if (parsing->west_texture)
            error_exit("West texture already defined");
        parsing->west_texture = path;
        printf("✅ West texture: %s\n", path);
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        if (parsing->east_texture)
            error_exit("East texture already defined");
        parsing->east_texture = path;
        printf("✅ East texture: %s\n", path);
    }
}
