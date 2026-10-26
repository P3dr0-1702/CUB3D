/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:52:56 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 11:57:03 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ghosts/ghosts.h"
#include "render3D.h"

void	render_targets(t_game *game)
{
	t_point			coord;
	t_point			pivot_coord;
	t_sprite_ref	target_tile;
	int				i;

	target_tile = game->sprite_sheet.sprites[253];
	i = 0;
	pivot_coord = pinky_target(game, 2);
	pivot_coord.x = (pivot_coord.x * 8) + game->scheme.x_pos;
	pivot_coord.y = (pivot_coord.y * 8) + game->scheme.y_pos;
	render_sprite_into_framebuffer(game, pivot_coord,
		&game->sprite_sheet.sprites[81]);
	while (i < 4)
	{
		coord.x = ((game->ghosts[i].target_tile.x * 8) + game->scheme.x_pos) % 1920;
		coord.y = ((game->ghosts[i].target_tile.y * 8) + game->scheme.y_pos) % 1080;
		render_sprite_into_framebuffer(game, coord, &target_tile);
		target_tile.coord.x += 200;
		i++;
	}
}

void	render_debug_symbols(t_game *game)
{
	render_raycast_debug(game);
	render_targets(game);
}
