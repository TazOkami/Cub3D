/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:34:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 17:34:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_color_line(char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
        return (true);
    if (ft_strncmp(line, "C ", 2) == 0)
        return (true);
    return (false);
}
