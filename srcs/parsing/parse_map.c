/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 17:34:34 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_map_line(char *line)
{
    int i = 0;
    
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
            line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
            line[i] != ' ')
            return (false);
        i++;
    }
    return (true);
}
