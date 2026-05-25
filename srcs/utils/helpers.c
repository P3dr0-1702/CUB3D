/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:01:19 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/21 15:19:02 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

int	distance_to_target(t_ghost *ghost, int dy, int dx)
{
	int	result;

	result = pow((((ghost->pos.pixel_pos.x / 8) + dx) - ghost->target_tile.x),
			2) + pow((((ghost->pos.pixel_pos.y / 8) + dy)
				- ghost->target_tile.y), 2);
	return (result);
}

int	change_game_mode(t_game *game)
{
	if (game->timer.mode >= 7)
		return (CHASE);
	else if (game->timer.mode % 2 == 0)
		return (SCATTER);
	return (CHASE);
}

bool	is_time_up(t_game *game, long now)
{
	return (game->timer.mode < 8 && game->state == PLAY
		&& game->timer.times[game->timer.mode] >= 0 && now
		- game->timer.mode_time_start
		> (long)(game->timer.times[game->timer.mode])
		* 1000000.0);
}
