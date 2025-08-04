/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:34 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 21:03:38 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include "struct.h"
# include "../libft/libft.h"

// ═══════════════════════════════════════════════════════════
// 🖥️ SCREEN CONSTANTS
// ═══════════════════════════════════════════════════════════
# define SCREEN_WIDTH 1536
# define SCREEN_HEIGHT 1024
# define TILE_SIZE 64
# define FOV 0.66
# define PI 3.14159265359
# define PI2 1.57079632679
# define PI3 4.71238898038

// ═══════════════════════════════════════════════════════════
// 🎮 KEY CODES
// ═══════════════════════════════════════════════════════════
# define KEY_W 122 // 119
# define KEY_A  113// 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

// ═══════════════════════════════════════════════════════════
// 🗺️ MAP CONSTANTS
// ═══════════════════════════════════════════════════════════
# define MAP_WIDTH 16
# define MAP_HEIGHT 12
# define WALL 1
# define EMPTY 0

// ═══════════════════════════════════════════════════════════
// 🎨 COLOR CONSTANTS
// ═══════════════════════════════════════════════════════════
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_GRAY 0x808080
# define COLOR_DARK_GRAY 0x404040

# include "struct.h"

// ═══════════════════════════════════════════════════════════
// 🎮 PLAYER MOVEMENT FUNCTIONS
// ═══════════════════════════════════════════════════════════
void	handle_player_movement(t_game *game);
void	move_player_forward(t_game *game);
void	move_player_backward(t_game *game);
void	rotate_player_left(t_game *game);
void	rotate_player_right(t_game *game);

// ═══════════════════════════════════════════════════════════
// 🎨 RENDERING FUNCTIONS
// ═══════════════════════════════════════════════════════════
void	render_scene(t_game *game);
void	cast_rays(t_game *game);
void	cast_single_ray(t_game *game, int x);
void	init_ray(t_ray *ray, t_game *game, int x);
void	perform_dda(t_ray *ray, t_game *game);
void	calculate_wall_distance(t_ray *ray, t_game *game);
void	draw_wall_column(t_game *game, t_ray *ray, int x);
void	draw_floor_and_ceiling(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);

// nouvelle fonction render_utils.c
t_texture	*select_wall_texture(t_game *game, t_ray *ray);
int get_texture_x(t_game *game, t_ray *ray, t_texture *texture);

// ═══════════════════════════════════════════════════════════
// 🖼️ TEXTURE FUNCTIONS
// ═══════════════════════════════════════════════════════════
int		load_textures(t_game *game);
void	free_textures(t_game *game);
int		get_texture_pixel(t_texture *texture, int x, int y);

// ═══════════════════════════════════════════════════════════
// 🗺️ MAP FUNCTIONS
// ═══════════════════════════════════════════════════════════
int		init_default_map(t_game *game);
int		load_map(char *filename, t_game *game);
void	free_map_grid(char **grid, int height);
int		is_wall_at(t_game *game, double x, double y);
int		get_map_cell(t_game *game, int x, int y);
void	init_game_defaults(t_game *game);
int		init_mlx(t_game *game);
void	set_player_direction(t_player *player, char direction);
void	set_player_from_map(t_vector2d *pos, char *dir,	t_map_pos pos_data);
bool	is_spawn(char c);
void	find_player_position(t_temp_map map, t_vector2d *pos, char *dir);
void	validate_map(char **map, int height, int width);
void	free_map_lines(char **map_lines, int count);

// ═══════════════════════════════════════════════════════════
// 📄 PARSING FUNCTIONS
// ═══════════════════════════════════════════════════════════
int		parse_cub_file(char *filename, t_parsing *parsing);
int		open_cub_file(char *filename);
int		check_parsing_complete(t_parsing *parsing);
void	parse_texture_line(char *line, t_parsing *parsing);
void	parse_color_line(char *line, t_parsing *parsing);
void	parse_map_line(char *line, t_parsing *parsing);
char	**build_final_map(t_parsing *parsing, t_player *player);
bool	is_texture_line(char *line);
bool	is_color_line(char *line);
bool	is_map_line(char *line);
bool	is_empty_line(char *line);
double	normalize_angle(double angle);
double	calculate_distance(double x1, double y1, double x2, double y2);

// ═══════════════════════════════════════════════════════════
// 🛠️ UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════
void	error_exit(char *message);
void	cleanup_and_exit(t_game *game, char *message);
void	cleanup_resources(t_game *game);
void	cleanup_game(t_game *game);
void	free_parsing_data(t_parsing *parsing);
int		handle_destroy(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);

#endif