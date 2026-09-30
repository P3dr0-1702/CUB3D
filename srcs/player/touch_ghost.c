/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_touch_ghost.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 15:42:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 18:41:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../../srcs/render/render3D.h"
#include "player3D.h"

static int	player_touching_ghost(t_game *g, t_ghost *p, double r)
{
	double	dx;
	double	dy;

	dx = g->player.pos.tile_pos.x - p->pos.tile_pos.x;
	dy = g->player.pos.tile_pos.y - p->pos.tile_pos.y;
	return ((dx * dx + dy * dy) <= (r * r));
}

void	play_death(t_game *game, t_point coord)
{
	int	i;

	i = 0;
	while (i < 12)
	{
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.death[i]);
		mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr,
			game->win.frame_buffer.img_ptr, 0, 0);
		usleep(1000);
		i++;
	}
}

static void	handle_player_death(t_game *g)
{
	g->player.lives--;
	play_death(g, (t_point){g->player.pos.pixel_pos.x,
		g->player.pos.pixel_pos.y});
	if (g->player.lives <= 0)
	{
			g->state = MENU;
			reset_game(g, 0);
	}
	reset_game(g, 1);
}

void	handle_ghost_touch(t_game *g)
{
	int	slayer;

	slayer = player_touched_ghost(g);
	if (!slayer)
		return ;
	if (g->ghosts[slayer - 1].state == FRIGHTENED)
		g->ghosts[slayer - 1].state = EATEN;
	else if (!g->debug_mode)
		handle_player_death(g);
}

int	player_touched_ghost(t_game *g)
{
	int	i;
	int	slayer;

	if (!g)
		return (0);
	i = 0;
	slayer = -1;
	while (i < 4)
	{
		if (g->ghosts[i].name != DISABLED && g->ghosts[i].state != EATEN
			&& player_touching_ghost(g, &g->ghosts[i], 1))
			slayer = i;
		i++;
	}
	if (slayer == -1)
		return (0);
	return (slayer + 1);
}
