/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:23:27 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 11:22:59 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int handle_keypress(int keycode, t_game *game)
{
	// t_vector2d move_dir;
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D
	|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
	game->last_key = keycode;
	if (keycode == KEY_ESC)
	{
		game->mlx.window_destroyed = true;
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
		exit(0);
	}

	// else if (keycode == KEY_W)
	// {
	// 	move_dir = game->player.direction;
	// 	move_player(game, move_dir);
	// }
	// else if (keycode == KEY_S)
	// {
	// 	move_dir.x = -game->player.direction.x;
	// 	move_dir.y = -game->player.direction.y;
	// 	move_player(game, move_dir);
	// }
	// else if (keycode == KEY_A)
	// {
	// 	move_dir.x = -game->player.direction.y;
	// 	move_dir.y = game->player.direction.x;
	// 	move_player(game, move_dir);
	// }
	// else if (keycode == KEY_D)
	// {
	// 	move_dir.x = game->player.direction.y;
	// 	move_dir.y = -game->player.direction.x;
	// 	move_player(game, move_dir);
	// }
	// else if (keycode == KEY_LEFT)
	// 	rotate_player(game, -game->player.rotation_speed);
	// else if (keycode == KEY_RIGHT)
	// 	rotate_player(game, game->player.rotation_speed);
	return (0);
}
