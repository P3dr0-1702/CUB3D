/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:43:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 11:44:24 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render3D.h"

void	render_pacdots_into_framebuffer(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->pacdot_count)
	{
		if (game->pacdots[i].active)
			render_sprite_into_framebuffer(game,
				(t_point){.y = game->pacdots[i].pos.pixel_pos.y + game->scheme.y_pos,
				.x = game->pacdots[i].pos.pixel_pos.x + game->scheme.x_pos},
				&game->sprite_sheet.sprites[37]);
		i++;
	}
}

void	render_energizers_into_framebuffer(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->energizer_count)
	{
		if (game->energizers[i].active)
			render_sprite_into_framebuffer(game,
				(t_point){.y = game->energizers[i].pos.pixel_pos.y + game->scheme.y_pos,
				.x = game->energizers[i].pos.pixel_pos.x + game->scheme.x_pos},
				&game->sprite_sheet.sprites[81]);
		i++;
	}
}
