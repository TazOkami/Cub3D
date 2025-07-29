/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:34 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/29 18:25:54 by Jpaulis          ###   ########.fr       */
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

#include "../libft/libft.h"
#include "struct.h"
#include "../minilibx-linux/mlx.h"
#include "keys.h"

// INIT
bool    init_game(t_game *game);
bool    init_mlx(t_game *game);
bool init_events(t_game *game);

// Parsing
int parse_cub_file(char *filename, t_parsing *parsing);
int open_cub_file(char *filename);
bool is_texture_line(char *line);
bool is_color_line(char *line);
bool is_map_line(char *line);
void    parse_texture_line(char *line, t_parsing *parsing);
void    parse_color_line(char *line, t_parsing *parsing);
void    parse_map_line(char *line, t_parsing *parsing);
int     check_parsing_complete(t_parsing *parsing);

// CONTROLS
int handle_keypress(int keycode, t_game *game);

// UTILS
int error_exit(char *message);
bool safe_malloc_check(void *ptr, char *context);
bool validate_file_extension(char *filename, char *extension);
void cleanup_game(t_game *game);
int close_window(t_game *game);


#endif