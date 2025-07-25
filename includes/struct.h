/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:23:39 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 19:01:14 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>

// ═══════════════════════════════════════════════════════════
// 📄 PARSING STRUCTURE
// Temporary structure to store parsed data from .cub file
// before transferring to main game structure
// ═══════════════════════════════════════════════════════════
typedef struct s_parsing
{
    char    *north_texture;     // Path to north wall texture file
    char    *south_texture;     // Path to south wall texture file
    char    *west_texture;      // Path to west wall texture file
    char    *east_texture;      // Path to east wall texture file
    int     floor_color;        // RGB color value for floor
    int     ceiling_color;      // RGB color value for ceiling
    bool    all_loaded;         // Flag: all required elements parsed
    
}   t_parsing;

// ═══════════════════════════════════════════════════════════
// 📐 2D VECTOR STRUCTURE
// Represents a point or direction in 2D space
// Used for positions, directions, and mathematical operations
// ═══════════════════════════════════════════════════════════
typedef struct s_vector2d
{
    double  x;                  // X coordinate or X component
    double  y;                  // Y coordinate or Y component
}   t_vector2d;

// ═══════════════════════════════════════════════════════════
// 🖼️ MLX CONTEXT STRUCTURE
// Contains all MLX-related pointers and image data
// Manages the display window and pixel buffer
// ═══════════════════════════════════════════════════════════
typedef struct s_mlx_context
{
    void    *mlx_ptr;           // MLX instance pointer
    void    *window_ptr;        // Window pointer
    void    *image_ptr;         // Image buffer pointer
    char    *image_data;        // Raw pixel data array
    int     bits_per_pixel;     // Color depth (usually 32)
    int     line_length;        // Bytes per image line
    int     endian;             // Byte order (big/little endian)
}   t_mlx_context;

// ═══════════════════════════════════════════════════════════
// 🎨 TEXTURE STRUCTURE
// Represents a single texture image with its properties
// Contains pixel data and dimensions for wall rendering
// ═══════════════════════════════════════════════════════════
typedef struct s_texture
{
    void            *image_ptr; // MLX image pointer
    unsigned int    *pixels;    // Array of pixel color values
    int             width;      // Texture width in pixels
    int             height;     // Texture height in pixels
}   t_texture;

// ═══════════════════════════════════════════════════════════
// 🏗️ TEXTURES COLLECTION STRUCTURE
// Contains all game textures and colors
// Central repository for visual assets
// ═══════════════════════════════════════════════════════════
typedef struct s_textures
{
    t_texture   north_wall;     // Texture for north-facing walls
    t_texture   south_wall;     // Texture for south-facing walls
    t_texture   east_wall;      // Texture for east-facing walls
    t_texture   west_wall;      // Texture for west-facing walls
    t_texture   sprite;         // Texture for sprites/objects
    int         floor_color;    // RGB color for floor rendering
    int         ceiling_color;  // RGB color for ceiling rendering
}   t_textures;

// ═══════════════════════════════════════════════════════════
// 🗺️ MAP INFORMATION STRUCTURE
// Contains the game map data and metadata
// Stores the 2D grid and map properties
// ═══════════════════════════════════════════════════════════
typedef struct s_map_info
{
    char    **grid;             // 2D array representing the map
    int     width;              // Map width in grid units
    int     height;             // Map height in grid units
    int     sprite_count;       // Number of sprites in map
}   t_map_info;

// ═══════════════════════════════════════════════════════════
// 🎮 PLAYER STRUCTURE
// Contains all player-related data
// Position, orientation, and movement parameters
// ═══════════════════════════════════════════════════════════
typedef struct s_player
{
    t_vector2d  position;       // Current position in map coordinates
    t_vector2d  direction;      // Direction vector (where player looks)
    t_vector2d  camera_plane;   // Camera plane for field of view
    double      move_speed;     // Movement speed multiplier
    double      rotation_speed; // Rotation speed in radians
}   t_player;

// ═══════════════════════════════════════════════════════════
// 🔍 RAY STRUCTURE
// Represents a single ray used in raycasting
// Contains all data needed for ray-wall intersection
// ═══════════════════════════════════════════════════════════
typedef struct s_ray
{
    t_vector2d  direction;      // Ray direction vector
    t_vector2d  delta_distance; // Distance between grid lines
    t_vector2d  side_distance;  // Distance to next grid line
    t_vector2d  map_position;   // Current map grid position
    t_vector2d  step;           // Step direction (+1 or -1)
    double      perpendicular_wall_distance; // Distance to wall
    int         hit_side;       // Wall side hit (0=NS, 1=EW)
    bool        wall_hit;       // Flag: ray hit a wall
}   t_ray;

// ═══════════════════════════════════════════════════════════
// 👻 SPRITE STRUCTURE
// Represents a sprite/object in the game world
// Used for rendering 2D objects in 3D space
// ═══════════════════════════════════════════════════════════
typedef struct s_sprite
{
    t_vector2d  position;       // Sprite position in map coordinates
    double      distance_from_player; // Distance for depth sorting
    int         texture_x;      // X coordinate in texture
    int         texture_y;      // Y coordinate in texture
}   t_sprite;

// ═══════════════════════════════════════════════════════════
// 🎬 RENDER INFORMATION STRUCTURE
// Contains calculated values for wall rendering
// Temporary data used during the rendering process
// ═══════════════════════════════════════════════════════════
typedef struct s_render_info
{
    int     line_height;        // Height of wall line to draw
    int     line_start;         // Start Y position for wall
    int     line_end;           // End Y position for wall
    int     texture_x;          // X coordinate in wall texture
    double  wall_x;             // Exact wall hit position
}   t_render_info;

// ═══════════════════════════════════════════════════════════
// 🎯 MAIN GAME STRUCTURE
// Central structure containing all game data
// The master structure that ties everything together
// ═══════════════════════════════════════════════════════════
typedef struct s_game
{
    t_mlx_context   mlx;        // MLX display context
    t_textures      textures;   // All textures and colors
    t_map_info      map;        // Map data and properties
    t_player        player;     // Player state and position
    t_sprite        *sprites;   // Array of sprites in the game
    bool            game_running; // Game loop control flag
    int				last_key;   // Last pressed key code
}   t_game;

#endif
