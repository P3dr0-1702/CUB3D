/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 18:37:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/23 11:16:15 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../../srcs/render/render3D.h"
#include "player3D.h"

static void	player_cube_controller(t_game *g)
{
	if (g->key.w)
		player_apply_action(g, MOVE_FORWARD);
	if (g->key.s)
		player_apply_action(g, MOVE_BACKWARD);
	if (g->key.d)
		player_apply_action(g, MOVE_RIGHT);
	if (g->key.a)
		player_apply_action(g, MOVE_LEFT);
	if (g->key.right)
		player_apply_action(g, ROTATE_RIGHT);
	if (g->key.left)
		player_apply_action(g, ROTATE_LEFT);
}

static void	player_pacman_controller(t_game *g)
{
	if (g->key.w || g->key.up)
		player_move(g, 0);
	if (g->key.s || g->key.down)
		player_move(g, 2);
	if (g->key.d || g->key.right)
		player_move(g, 3);
	if (g->key.a || g->key.left)
		player_move(g, 1);
	update_player_direction(g, 1);
	apply_player_movement(g, g->player.target_dir.x * PLAYER_SPEED,
		g->player.target_dir.y * PLAYER_SPEED);
}

void	player_controller(t_game *g)
{
	if (!g)
		return ;
	if (g->mode == MODE_CUBE || g->mode == MODE_FREE_ROAM)
		player_cube_controller(g);
	else if (g->mode == MODE_PACMAN)
		player_pacman_controller(g);
}
