/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:33:44 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/24 17:41:21 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game game;
    
    if (argc != 2)
    {
        printf("Usage: ./cub3D <map.cub>\n");
        return (1);
    }
    
    // Parser la map
    if (parse_map(argv[1], &game) == -1)
        return (1);
        
    // Initialiser le jeu
    if (init_game(&game) == -1)
        return (1);

	return (0);

}