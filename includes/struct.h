/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:23:39 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/24 17:35:55 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_player {
    double x;           // Position
	double y;
    double dir_x;   // Direction
	double dir_y;
    double plane_x; // Plan de caméra 0
	double plane_y; // 0.66
	double move_speed;
	double rot_speed;
	double angle;
} t_player;

typedef struct s_map {
    char **grid;
    int width;
	int height;
    char *no_texture;      // Nord
    char *so_texture;      // Sud  
    char *we_texture;      // Ouest
    char *ea_texture;      // Est
    int floor_color[3];
    int ceiling_color[3];
} t_map;

typedef struct s_image {
	void *img;
	char *img_data;
	char *addr;
	int bits_per_pixel; //bits per pixel (32 bits = 4 bytes/pixel ARGB)
	int line_length; // Taille de ligne en bytes
	int endian; // 0 = little endian, 1 = big endian (ordre des bytes dans la mémoire)
} t_image;

typedef struct s_game {
    void *mlx;
    void *win;
	t_image img;
	int win_width;
	int win_height;
    t_player player;
    t_map map;
    
} t_game;

#endif