/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:13:29 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 15:34:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void error_exit(char *message)
{
	printf("❌ Error: %s\n", message);
	exit(EXIT_FAILURE);
}

bool safe_malloc_check(void *ptr, char *context)
{
	if (!ptr)
	{
		printf("❌ Malloc failed in: %s\n", context);
		return (false);
	}
	return (true);
}

bool validate_file_extension(char *filename, char *extension)
{
	int filename_len;
	int ext_len;
	
	if (!filename || !extension)
		return (false);

	filename_len = strlen(filename);
	ext_len = strlen(extension);
	if (filename_len < ext_len)
		return (false);
	return (strcmp(filename + filename_len - ext_len, extension) == 0);
}
