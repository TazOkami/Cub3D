/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:58 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 15:12:35 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_player_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.position.x + game->player.direction.x
			* game->player.move_speed;
	new_y = game->player.position.y + game->player.direction.y
			* game->player.move_speed;

	if (!is_wall_at(game, new_x, new_y))
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	move_player_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.position.x - game->player.direction.x
			* game->player.move_speed;
	new_y = game->player.position.y - game->player.direction.y
			* game->player.move_speed;

	if (!is_wall_at(game, new_x, new_y))
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	rotate_player_left(t_game *game)
{
	double	old_dir_x;
	double old_plane_x;
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
	game->player.camera_plane.y = old_plane_x * sin(-game->player.rotation_speed)
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
	game->player.camera_plane.y = old_plane_x * sin(game->player.rotation_speed)
									+ game->player.camera_plane.y
									* cos(game->player.rotation_speed);

}
