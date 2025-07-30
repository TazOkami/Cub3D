/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:22:12 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 12:41:20 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool is_empty_line(char *line)
{
    int i = 0;
    
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
            return (false);
        i++;
    }
    return (true);
}

int open_cub_file(char *filename)
{
	int fd;

	if (!ft_strstr(filename, ".cub"))
	{
		printf("Error: File must have .cub extension\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening .cub file");
		return (-1);
	}
	printf("✅ File %s opened successfully\n", filename);
	return (fd);
}

int parse_cub_file(char *filename, t_parsing *parsing)
{
    int fd;
    char *line;
    
    fd = open_cub_file(filename);
    if (fd < 0)
        return (0);
        
    while ((line = get_next_line(fd)) != NULL)
    {
        if (is_empty_line(line))
        {
            free(line);
            continue;
        }
        else if (is_texture_line(line))
            parse_texture_line(line, parsing);
        else if (is_color_line(line))
            parse_color_line(line, parsing);  
        else if (is_map_line(line))
            parse_map_line(line, parsing);
        else
        {
            free(line);  // ⭐ IMPORTANT : free avant error_exit !
            close(fd);
            error_exit("Invalid line in .cub file");
        }
        free(line);
    }
    close(fd);
    return (check_parsing_complete(parsing));
}

// Dans parsing/utils.c ou parser.c
bool	is_texture_line(char *line)
{
    return (ft_strncmp(line, "NO ", 3) == 0 || 
            ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 || 
            ft_strncmp(line, "EA ", 3) == 0);
}

bool	is_color_line(char *line)
{
    return ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ');
}

char	**realloc_map_lines(char **old_lines, int new_size)
{
    char	**new_lines;
    int		i;
    
    new_lines = malloc(sizeof(char*) * new_size);
    if (!new_lines)
        return (NULL);
    
    i = 0;
    while (i < new_size - 1 && old_lines)
    {
        new_lines[i] = old_lines[i];
        i++;
    }
    
    if (old_lines)
        free(old_lines);
    return (new_lines);
}

void	free_split(char **split)
{
    int	i = 0;
    
    if (!split)
        return ;
    while (split[i])
        free(split[i++]);
    free(split);
}

void	parse_texture_line(char *line, t_parsing *parsing)
{
    char	*trimmed;
    
    trimmed = ft_strtrim(line, " \t\n");
    if (!trimmed)
        return ;
    
    if (ft_strncmp(trimmed, "NO ", 3) == 0)
        parsing->north_texture = ft_strdup(trimmed + 3);
    else if (ft_strncmp(trimmed, "SO ", 3) == 0)
        parsing->south_texture = ft_strdup(trimmed + 3);
    else if (ft_strncmp(trimmed, "WE ", 3) == 0)
        parsing->west_texture = ft_strdup(trimmed + 3);
    else if (ft_strncmp(trimmed, "EA ", 3) == 0)
        parsing->east_texture = ft_strdup(trimmed + 3);
    
    free(trimmed);
}

void parse_color_line(char *line, t_parsing *parsing)
{
    char *trimmed = ft_strtrim(line, " \t\n");
    char **split;
    
    if (!trimmed)
        return;
        
    if (ft_strncmp(trimmed, "F ", 2) == 0)
    {
        // Parse Floor color
        char *color_str = ft_strtrim(trimmed + 2, " \t");
        split = ft_split(color_str, ',');
        
        if (split && split[0] && split[1] && split[2] && !split[3])
        {
            parsing->floor_color[0] = ft_atoi(split[0]);      // R
            parsing->floor_color[1] = ft_atoi(split[1]);      // G  
            parsing->floor_color[2] = ft_atoi(split[2]);      // B
        }
        
        free_split(split);
        free(color_str);
    }
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
    {
        // Parse Ceiling color
        char *color_str = ft_strtrim(trimmed + 2, " \t");
        split = ft_split(color_str, ',');
        
        if (split && split[0] && split[1] && split[2] && !split[3])
        {
            parsing->ceiling_color[0] = ft_atoi(split[0]);    // R
            parsing->ceiling_color[1] = ft_atoi(split[1]);    // G
            parsing->ceiling_color[2] = ft_atoi(split[2]);    // B
        }
        
        free_split(split);
        free(color_str);
    }
    
    free(trimmed);
}

bool check_parsing_complete(t_parsing *parsing)
{
    // ✅ Vérifier les textures
    if (!parsing->north_texture || !parsing->south_texture || 
        !parsing->west_texture || !parsing->east_texture)
    {
        printf("❌ Missing texture files\n");
        return (false);
    }
    
    // ✅ Vérifier les couleurs du sol
    if (parsing->floor_color[0] < 0 || parsing->floor_color[0] > 255 ||
        parsing->floor_color[1] < 0 || parsing->floor_color[1] > 255 ||
        parsing->floor_color[2] < 0 || parsing->floor_color[2] > 255)
    {
        printf("❌ Invalid floor color values\n");
        return (false);
    }
    
    // ✅ Vérifier les couleurs du plafond
    if (parsing->ceiling_color[0] < 0 || parsing->ceiling_color[0] > 255 ||
        parsing->ceiling_color[1] < 0 || parsing->ceiling_color[1] > 255 ||
        parsing->ceiling_color[2] < 0 || parsing->ceiling_color[2] > 255)
    {
        printf("❌ Invalid ceiling color values\n");
        return (false);
    }
    
    // ✅ Pour l'instant, on valide juste les textures et couleurs
    // La map sera validée dans une fonction séparée
    
    parsing->all_loaded = true;
    printf("✅ Basic parsing complete\n");
    return (true);
}
