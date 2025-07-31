/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:44:30 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/31 15:49:05 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_single_texture(void *mlx_ptr, t_texture *texture, char *path)
{
	int	width;
	int	height;

	if (!path)
	{
		printf("❌ Texture path is NULL\n");
		return (1);
	}
	texture->image_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &width, &height);
	if (!texture->image_ptr)
	{
		printf("❌ Failed to load texture: %s\n", path);
		return (1);
	}
	texture->width = width;
	texture->height = height;
	texture->pixels = (unsigned int *)mlx_get_data_addr(texture->image_ptr,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (!texture->pixels)
	{
		printf("❌ Failed to get texture data: %s\n", path);
		mlx_destroy_image(mlx_ptr, texture->image_ptr);
		return (1);
	}
	return (0);
}

int	load_textures(t_game *game)
{
	printf("🖼️ Loading textures...\n");
	if (load_single_texture(game->mlx.mlx_ptr, &game->textures.north_wall,
			game->textures.north_path))
		return (1);
	if (load_single_texture(game->mlx.mlx_ptr, &game->textures.south_wall,
			game->textures.south_path))
		return (1);
	if (load_single_texture(game->mlx.mlx_ptr, &game->textures.east_wall,
			game->textures.east_path))
		return (1);
	if (load_single_texture(game->mlx.mlx_ptr, &game->textures.west_wall,
			game->textures.west_path))
		return (1);
	printf("✅ All textures loaded successfully!\n");
	return (0);
}

void	free_textures(t_game *game)
{
	if (game->textures.north_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.north_wall.image_ptr);
	if (game->textures.south_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.south_wall.image_ptr);
	if (game->textures.east_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.east_wall.image_ptr);
	if (game->textures.west_wall.image_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->textures.west_wall.image_ptr);
	printf("🧹 Textures freed\n");
}

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	if (!texture || !texture->pixels)
		return (0);
	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	return (texture->pixels[y * texture->width + x]);
}
