/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:34:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 14:30:50 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/cub3d.h"
#include <stdio.h>

bool is_color_line(char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
        return (true);
    if (ft_strncmp(line, "C ", 2) == 0)
        return (true);
    return (false);
}

static int parse_rgb_value(char *str)
{
    int value;

    value = ft_atoi(str);
    if (value < 0 || value > 255)
        error_exit("RGB value must be between 0 and 255");
    return (value);
}

static void parse_rgb_string(char *line, int *rgb)
{
    char **parts;
    int i = 0;

    // Skip identifier (F or C)
    while (line[i] && line[i] != ' ')
        i++;
    // Skip spaces
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    parts = ft_split(line + i, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2])
        error_exit("Invalid RGB format. Expected: R,G,B");

    rgb[0] = parse_rgb_value(parts[0]);
    rgb[1] = parse_rgb_value(parts[1]);
    rgb[2] = parse_rgb_value(parts[2]);

    // Check if there are more than 3 values
    if (parts[3])
        error_exit("Too many RGB values");

    // Free split array
    i = 0;
    while (parts[i])
    {
        free(parts[i]);
        i++;
    }
    free(parts);
}

void parse_color_line(char *line, t_parsing *parsing)
{
    if (ft_strncmp(line, "F ", 2) == 0)
    {
        if (parsing->floor_color[0] != -1)
            error_exit("Floor color already defined");
        parse_rgb_string(line, parsing->floor_color);
        printf("✅ Floor color: %d,%d,%d\n",
               parsing->floor_color[0],
               parsing->floor_color[1],
               parsing->floor_color[2]);
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        if (parsing->ceiling_color[0] != -1)
            error_exit("Ceiling color already defined");
        parse_rgb_string(line, parsing->ceiling_color);
        printf("✅ Ceiling color: %d,%d,%d\n",
               parsing->ceiling_color[0],
               parsing->ceiling_color[1],
               parsing->ceiling_color[2]);
    }
}
