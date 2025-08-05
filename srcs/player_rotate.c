/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:38:03 by malafont          #+#    #+#             */
/*   Updated: 2025/08/04 15:38:05 by malafont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	rotate_player_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.direction.x;
	old_plane_x = game->player.camera_plane.x;
	game->player.direction.x = game->player.direction.x
		* cos(-game->player.rotation_speed)
		- game->player.direction.y
		* sin(-game->player.rotation_speed);
	game->player.direction.y = old_dir_x * sin(-game->player.rotation_speed)
		+ game->player.direction.y
		* cos(-game->player.rotation_speed);
	game->player.camera_plane.x = game->player.camera_plane.x
		* cos(-game->player.rotation_speed)
		- game->player.camera_plane.y
		* sin(-game->player.rotation_speed);
	game->player.camera_plane.y = old_plane_x
		* sin(-game->player.rotation_speed)
		+ game->player.camera_plane.y
		* cos(-game->player.rotation_speed);
}

void	rotate_player_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.direction.x;
	old_plane_x = game->player.camera_plane.x;
	game->player.direction.x = game->player.direction.x
		* cos(game->player.rotation_speed)
		- game->player.direction.y
		* sin(game->player.rotation_speed);
	game->player.direction.y = old_dir_x * sin(game->player.rotation_speed)
		+ game->player.direction.y
		* cos(game->player.rotation_speed);
	game->player.camera_plane.x = game->player.camera_plane.x
		* cos(game->player.rotation_speed)
		- game->player.camera_plane.y
		* sin(game->player.rotation_speed);
	game->player.camera_plane.y = old_plane_x
		* sin(game->player.rotation_speed)
		+ game->player.camera_plane.y
		* cos(game->player.rotation_speed);
}
