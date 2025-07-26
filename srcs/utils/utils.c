/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:08:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 16:08:49 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *ft_strdup(const char *s)
{
    int len = strlen(s);
    char *dup = malloc(len + 1);
    int i = 0;
    
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