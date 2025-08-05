/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:21:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/08/05 15:13:57 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game_defaults(t_game *game)
{
	game->game_running = true;
	game->last_key = 0;
	game->player.position.x = 1.5;
	game->player.position.y = 1.5;
	game->player.direction.x = 1.0;
	game->player.direction.y = 0.0;
	game->player.camera_plane.x = 0.0;
	game->player.camera_plane.y = 0.66;
	game->player.move_speed = 0.1;
	game->player.rotation_speed = 0.05;
	game->map.width = 8;
	game->map.height = 8;
	game->map.sprite_count = 0;
	game->map.grid = NULL;
	game->textures.floor_color = 0x808080;
	game->textures.ceiling_color = 0x404040;
}

int	init_mlx(t_game *game)
{
	ft_memset(&game->mlx, 0, sizeof(t_mlx_context));
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (1);
	game->mlx.window_ptr = mlx_new_window(game->mlx.mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D - Raycasting");
	if (!game->mlx.window_ptr)
		return (1);
	game->mlx.image_ptr = mlx_new_image(game->mlx.mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->mlx.image_ptr)
		return (1);
	game->mlx.image_data = mlx_get_data_addr(game->mlx.image_ptr,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);
	if (!game->mlx.image_data)
		return (1);
	game->mlx.window_destroyed = false;
	return (0);
}

static void	set_ns_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->direction.x = 0.0;
		player->direction.y = -1.0;
		player->camera_plane.x = 0.66;
		player->camera_plane.y = 0.0;
	}
	else
	{
		player->direction.x = 0.0;
		player->direction.y = 1.0;
		player->camera_plane.x = -0.66;
		player->camera_plane.y = 0.0;
	}
}

static void	set_ew_direction(t_player *player, char direction)
{
	if (direction == 'E')
	{
		player->direction.x = 1.0;
		player->direction.y = 0.0;
		player->camera_plane.x = 0.0;
		player->camera_plane.y = 0.66;
	}
	else
	{
		player->direction.x = -1.0;
		player->direction.y = 0.0;
		player->camera_plane.x = 0.0;
		player->camera_plane.y = -0.66;
	}
}

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N' || direction == 'S')
		set_ns_direction(player, direction);
	else if (direction == 'E' || direction == 'W')
		set_ew_direction(player, direction);
	else
		error_exit("Invalid player direction");
}
