#include "../../includes/cub3d.h"

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

void	handle_player_movement(t_game *game)
{
	if (game->keys[KEY_W])
		move_player_forward(game);
	if (game->keys[KEY_S])
		move_player_backward(game);
	if (game->keys[KEY_A] || game->keys[KEY_LEFT])
		rotate_player_left(game);
	if (game->keys[KEY_D] || game->keys[KEY_RIGHT])
		rotate_player_right(game);
}

