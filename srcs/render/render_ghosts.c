/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ghosts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 11:41:10 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/15 11:42:22 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render3D.h"
#include "../ghosts/ghosts.h"

void	render_normal_ghost(t_game *game, t_point coord, t_ghost *ghost)
{
	if (ghost->invalid_dir == 0)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.down[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
	if (ghost->invalid_dir == 1)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.right[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
	if (ghost->invalid_dir == 2)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.up[((ghost->pos.pixel_pos.x + ghost->pos.pixel_pos.y)
				% 2)]);
	if (ghost->invalid_dir == 3)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.left[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
}

void	render_eaten_ghost(t_game *game, t_point coord, t_ghost *ghost)
{
	if (ghost->invalid_dir == 0)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.down[2]);
	if (ghost->invalid_dir == 1)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.right[2]);
	if (ghost->invalid_dir == 2)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.up[2]);
	if (ghost->invalid_dir == 3)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.left[2]);
}

void	render_elroy_cruiser(t_game *game, t_point coord, t_ghost *ghost)
{
	if (ghost->invalid_dir == 0)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.down[3]);
	if (ghost->invalid_dir == 1)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.right[3]);
	if (ghost->invalid_dir == 2)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.up[3]);
	if (ghost->invalid_dir == 3)
		render_sprite_into_framebuffer(game, coord, &ghost->frames.left[3]);
}

void	render_ghost_into_framebuffer(t_game *game, t_point coord,
		t_ghost *ghost)
{
	if (ghost->state == FRIGHTENED)
		render_sprite_into_framebuffer(game, coord,
			&ghost->frames.scared[((ghost->pos.pixel_pos.x
					+ ghost->pos.pixel_pos.y) % 2)]);
	else
	{
		if (game->debug_mode && (ghost->cruiser.is_blinky
				&& (ghost->cruiser.one.enabled || ghost->cruiser.two.enabled)))
			render_elroy_cruiser(game, coord, ghost);
		else if (ghost->state != EATEN)
			render_normal_ghost(game, coord, ghost);
		else
			render_eaten_ghost(game, coord, ghost);
	}
}

void	render_ghosts_into_framebuffer(t_game *game)
{
	int		i;
	t_point	coord;

	i = -1;
	while (++i < 4)
	{
		if (ghost_ai(game, &game->ghosts[i]))
			continue ;
		coord.x = (game->ghosts[i].pos.pixel_pos.x - TILE_SIZE + game->scheme.x_pos);
		coord.y = (game->ghosts[i].pos.pixel_pos.y - TILE_SIZE + game->scheme.y_pos);
		render_ghost_into_framebuffer(game, coord, &game->ghosts[i]);
	}
}
