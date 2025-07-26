/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:08:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 19:14:26 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_strdup(const char *s)
{
	int len;
	char *dup;
	int i;
	
	len = strlen(s);
	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int close_window(t_game *game)
{
    printf("🚪 Closing window...\n");
    game->game_running = false;
    exit(0);
    return (0);
}

