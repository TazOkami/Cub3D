/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:22:12 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 18:20:17 by Jpaulis          ###   ########.fr       */
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
			error_exit("Invalid line in .cub file");
        free(line);
    }
    close(fd);
    return (check_parsing_complete(parsing));
}


// Stubs temporaires pour éviter les erreurs
void parse_texture_line(char *line, t_parsing *parsing)
{
    (void)line;
    (void)parsing;
    printf("🚧 parse_texture_line() - À implémenter\n");
}

void parse_color_line(char *line, t_parsing *parsing)
{
    (void)line;
    (void)parsing;
    printf("🚧 parse_color_line() - À implémenter\n");
}

void parse_map_line(char *line, t_parsing *parsing)
{
    (void)line;
    (void)parsing;
    printf("🚧 parse_map_line() - À implémenter\n");
}

int check_parsing_complete(t_parsing *parsing)
{
    (void)parsing;
    printf("🚧 check_parsing_complete() - À implémenter\n");
    return (1);  // OK temporaire
}
