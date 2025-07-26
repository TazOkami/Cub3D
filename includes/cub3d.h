/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:34 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 16:09:08 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

#include "struct.h"
#include "../minilibx-linux/mlx.h"
#include "keys.h"

// INIT
bool    init_game(t_game *game);
bool    init_mlx(t_game *game);

// Parsing
bool    parse_file(t_game *game, char *filename);
bool    parse_textures(t_game *game, char *line);
bool    parse_colors(t_game *game, char *line);
bool    parse_map_line(t_game *game, char *line);

// UTILS
void error_exit(char *message);
bool safe_malloc_check(void *ptr, char *context);
bool validate_file_extension(char *filename, char *extension);
void cleanup_game(t_game *game);
char *ft_strdup(const char *s);

#endif