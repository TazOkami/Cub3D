/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:38:03 by malafont          #+#    #+#             */
/*   Updated: 2025/08/04 15:38:05 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	free_map_lines(char **map_lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(map_lines[i]);
		i++;
	}
	free(map_lines);
}
