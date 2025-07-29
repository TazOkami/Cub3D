/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:31 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 17:33:47 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
