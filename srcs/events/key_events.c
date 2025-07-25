/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:12:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/24 17:43:29 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	key_press(int key, t_game *game)
// {
//     if (key == KEY_ESC)
//         exit_game(game);
//     else if (key == KEY_W)
//         move_forward(game);
//     else if (key == KEY_S)
//         move_backward(game);
//     else if (key == KEY_A)
//         move_left(game);
//     else if (key == KEY_D)
//         move_right(game);
//     else if (key == KEY_LEFT)
//         rotate_left(game);
//     else if (key == KEY_RIGHT)
//         rotate_right(game);
    
//     return (0);
// }
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return (0);
}
