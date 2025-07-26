/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:21:20 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 19:18:40 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool init_events(t_game *game)
{
	mlx_hook(game->mlx.window_ptr, 17, 1L<<17, close_window, game);
	mlx_key_hook(game->mlx.window_ptr, handle_keypress, game);
	return (true);
}

bool init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (false);
	game->mlx.window_ptr = mlx_new_window(game->mlx.mlx_ptr, 
										 WIN_WIDTH, WIN_HEIGHT, 
										 "Cub3D");
	if (!game->mlx.window_ptr)
		return (false);
	game->mlx.image_ptr = mlx_new_image(game->mlx.mlx_ptr, 
									   WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx.image_ptr)
		return (false);
	game->mlx.image_data = mlx_get_data_addr(game->mlx.image_ptr,
											&game->mlx.bits_per_pixel,
											&game->mlx.line_length,
											&game->mlx.endian);
	printf("✅ MLX initialized successfully\n");
	init_events(game);
	return (true);
}

