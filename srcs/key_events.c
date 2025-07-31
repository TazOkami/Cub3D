/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:12:03 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 15:36:23 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
		exit(0);
	}
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = true;
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = false;
	return (0);
}
