/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malafont <malafont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:00:00 by malafont         #+#    #+#             */
/*   Updated: 2025/07/30 15:00:00 by malafont         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/cub3d.h"
#include <stdio.h>

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	cleanup_and_exit(t_game *game, char *message)
{
	if (game)
		cleanup_game(game);
	error_exit(message);
}
