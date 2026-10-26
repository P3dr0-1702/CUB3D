/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 22:42:10 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:54:42 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

int	player_hits_wall(t_game *g, int row, int col)
{
	char	tile;

	tile = map_get_tile(g, row, col, 1);
	if (tile == WALL || tile == 'M' || tile == VOID)
		return (1);
	if (tile == GATE && g->gate_passable == 0)
		return (1);
	return (0);
}

int	ghost_hits_wall(t_game *g, int row, int col)
{
	char	tile;

	tile = map_get_tile(g, row, col, 1);
	if (tile == WALL || tile == 'M' || tile == VOID)
		return (1);
	if (tile == GATE && g->gate_passable == 0)
		return (1);
	return (0);
}

void	player_collision(t_game *g)
{
	t_player	*player;
	int			col;
	int			row;

	player = &g->player;
	row = (int)player->pos.tile_pos.y;
	col = (int)(player->pos.tile_pos.x - g->player.player_radius);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.x = col + 1 + g->player.player_radius;
	col = (int)(player->pos.tile_pos.x + g->player.player_radius);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.x = col - g->player.player_radius;
	col = (int)player->pos.tile_pos.x;
	row = (int)(player->pos.tile_pos.y - g->player.player_radius);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.y = row + 1 + g->player.player_radius;
	row = (int)(player->pos.tile_pos.y + g->player.player_radius);
	if (player_hits_wall(g, row, col))
		player->pos.tile_pos.y = row - g->player.player_radius;
}
