/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:58 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 16:57:22 by Jpaulis          ###   ########.fr       */
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

void	move_player_right(t_game *game)
{
	t_vector2d	right;
	double		new_x;
	double		new_y;

	right.x = game->player.direction.y;
	right.y = -game->player.direction.x;
	new_x = game->player.position.x - right.x * game->player.move_speed;
	new_y = game->player.position.y - right.y * game->player.move_speed;
	if (!is_wall_at(game, new_x, new_y))
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}
void	move_player_left(t_game *game)
{
	t_vector2d	right;
	double		new_x;
	double		new_y;

	right.x = game->player.direction.y;
	right.y = -game->player.direction.x;
	new_x = game->player.position.x + right.x * game->player.move_speed;
	new_y = game->player.position.y + right.y * game->player.move_speed;
	if (!is_wall_at(game, new_x, new_y))
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}