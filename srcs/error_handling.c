/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   error_handling.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/07/31 15:42:19 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/08/06 15:54:24 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	handle_destroy(t_game *game)
{
	printf("🔄 Window closed - cleaning up...\n");
	cleanup_game(game);
	exit(0);
	return (0);
}
