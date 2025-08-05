/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 01:36:03 by  jpaulis          #+#    #+#             */
/*   Updated: 2025/07/31 21:10:45 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strstr - Cherche la première occurrence
// de la chaîne needle dans la chaîne haystack
// Retourne un pointeur vers le début
// de la chaîne trouvée, ou NULL si needle n'est pas trouvée
// #include <stddef.h>

#include "libft.h"

// char	*ft_strstr(const char *haystack, const char *needle)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	if (!*needle)
// 		return ((char *)haystack);
// 	while (*haystack)
// 	{
// 		j = 0;
// 		while (haystack[i + j] == needle[j])
// 		{
// 			if (needle[j + 1] == '\0')
// 				return ((char *)(&haystack[i]));
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}


// #include <stdio.h>
// #include <string.h>

// int main() {
// 	const char *haystack = "Hello, world!";
// 	const char *needle = "z";
// 	char *result = strstr(haystack, needle);

// 	if (result) {
// 		printf("Found: %s\n", result);
// 	} else {
// 		printf("Not found\n");
// 	}

// 	return 0;
// }

