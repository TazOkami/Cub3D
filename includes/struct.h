/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:23:39 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 15:56:25 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>

typedef struct s_parsing
{
    char    *north_texture;
    char    *south_texture; 
    char    *west_texture;
    char    *east_texture;
    int     floor_color;
    int     ceiling_color;
    bool    all_loaded;
    
}   t_parsing;

typedef struct s_vector2d
{
	double  x;
	double  y;
}   t_vector2d;

typedef struct s_mlx_context
{
	void    *mlx_ptr;
	void    *window_ptr;
	void    *image_ptr;
	char    *image_data;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
}   t_mlx_context;

typedef struct s_texture
{
	void            *image_ptr;
	unsigned int    *pixels;
	int             width;
	int             height;
}   t_texture;

typedef struct s_textures
{
	t_texture   north_wall;
	t_texture   south_wall;
	t_texture   east_wall;
	t_texture   west_wall;
	t_texture   sprite;
	int         floor_color;
	int         ceiling_color;
}   t_textures;

typedef struct s_map_info
{
	char    **grid;
	int     width;
	int     height;
	int     sprite_count;
}   t_map_info;

typedef struct s_player
{
	t_vector2d  position;
	t_vector2d  direction;
	t_vector2d  camera_plane;
	double      move_speed;
	double      rotation_speed;
}   t_player;

typedef struct s_ray
{
	t_vector2d  direction;
	t_vector2d  delta_distance;
	t_vector2d  side_distance;
	t_vector2d  map_position;
	t_vector2d  step;
	double      perpendicular_wall_distance;
	int         hit_side; // 0 = NS, 1 = EW
	bool        wall_hit;
}   t_ray;

typedef struct s_sprite
{
	t_vector2d  position;
	double      distance_from_player;
	int         texture_x;
	int         texture_y;
}   t_sprite;

typedef struct s_render_info
{
	int     line_height;
	int     line_start;
	int     line_end;
	int     texture_x;
	double  wall_x;
}   t_render_info;

typedef struct s_game
{
	t_mlx_context   mlx;
	t_textures      textures;
	t_map_info      map;
	t_player        player;
	t_sprite        *sprites;
	bool            game_running;
	int				last_key;
}   t_game;

#endif