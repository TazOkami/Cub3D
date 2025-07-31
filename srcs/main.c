/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/30 14:55:42 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

static void	init_game_defaults(t_game *game)
{
	game->game_running = true;
	game->last_key = 0;

	// Initialiser le joueur
	game->player.position.x = 1.5;
	game->player.position.y = 1.5;
	game->player.direction.x = 1.0;
	game->player.direction.y = 0.0;
	game->player.camera_plane.x = 0.0;
	game->player.camera_plane.y = 0.66;
	game->player.move_speed = 0.1;
	game->player.rotation_speed = 0.05;

	// Initialiser la map par défaut
	game->map.width = 8;
	game->map.height = 8;
	game->map.sprite_count = 0;
	game->map.grid = NULL;

	// Initialiser les couleurs par défaut
	game->textures.floor_color = 0x808080;
	game->textures.ceiling_color = 0x404040;
}

static int	init_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (!game->mlx.mlx_ptr)
		return (1);

	game->mlx.window_ptr = mlx_new_window(game->mlx.mlx_ptr,
											SCREEN_WIDTH, SCREEN_HEIGHT,
											"Cub3D - Raycasting");
	if (!game->mlx.window_ptr)
		return (1);

	game->mlx.image_ptr = mlx_new_image(game->mlx.mlx_ptr,
										SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->mlx.image_ptr)
		return (1);

	game->mlx.image_data = mlx_get_data_addr(game->mlx.image_ptr,
											&game->mlx.bits_per_pixel,
											&game->mlx.line_length,
											&game->mlx.endian);
	if (!game->mlx.image_data)
		return (1);

	game->mlx.window_destroyed = false;
	return (0);
}

// void	cleanup_game(t_game *game)
// {
// 	if (game->mlx.image_ptr)
// 		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.image_ptr);
// 	if (game->mlx.window_ptr)
// 		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window_ptr);
// 	if (game->mlx.mlx_ptr)
// 		mlx_destroy_display(game->mlx.mlx_ptr);
// 	if (game->mlx.mlx_ptr)
// 		free(game->mlx.mlx_ptr);
// 	if (game->map.grid)
// 		free_map_grid(game->map.grid, game->map.height);
// 	if (game->sprites)
// 		free(game->sprites);
// 	free_textures(game);
// }

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
