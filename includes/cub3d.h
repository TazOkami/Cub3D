/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:34 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/25 16:11:55 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "struct.h"
#include "../minilibx-linux/minilibx-linux/mlx.h"
#include "keys.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define CENTER_X (WINDOW_WIDTH / 2)
# define CENTER_Y (WINDOW_HEIGHT / 2)

// EVENTS
int key_press(int keycode, t_game *game);
int close_window(t_game *game);

// INIT
int init_game(t_game *game);

// PARSING
int parse_map(char *filename, t_game *game);

// RENDERING
void put_pixel(t_image *img, int x, int y, int color);
void draw_background(t_game *game);
void draw_crosshair(t_game *game);
void render_frame(t_game *game);

#endif