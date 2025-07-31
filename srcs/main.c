/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 15:06:38 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	handle_keypress(int keycode, t_game *game)
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

static int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = false;
	return (0);
}

static int	handle_destroy(t_game *game)
{
	game->game_running = false;
	mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
	exit(0);

	return (0);
}

static int	game_loop(t_game *game)
{
	if (!game->game_running)
		return (0);

	handle_player_movement(game);
	render_scene(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window_ptr,
							game->mlx.image_ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Usage: ./cub3d <map.cub>\n", 2);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	init_game_defaults(&game);
	if (init_mlx(&game))
		cleanup_and_exit(&game, "MLX initialization failed");
	if (load_map(argv[1], &game))
		cleanup_and_exit(&game, "Map loading failed");
	if (load_textures(&game))
		cleanup_and_exit(&game, "Texture loading failed");
	mlx_hook(game.mlx.window_ptr, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.mlx.window_ptr, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.mlx.window_ptr, 17, 0, handle_destroy, &game);
	mlx_loop_hook(game.mlx.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
	cleanup_game(&game);
	return (0);
}
