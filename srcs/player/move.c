/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:24:25 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 18:37:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../../srcs/render/render3D.h"
#include "player3D.h"

static bool	safe_is_wall(t_map map, int y, int x)
{
	if (y < 0 || y >= map.height)
		return (true);
	if (x < 0)
		return (true);
	if (x >= (int)ft_strlen(map.grid[y]))
		return (true);
	return (map.grid[y][x] == '1' || map.grid[y][x] == 'G');
}

bool	can_move(t_game *game, int dir)
{
	static int	direction[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
	int			y;
	int			x;

	y = (int)game->player.pos.tile_pos.y + direction[dir][0];
	x = (int)game->player.pos.tile_pos.x + direction[dir][1];
	return (!safe_is_wall(game->map, y, x));
}

static void	set_player_target(t_game *g, double dx, double dy)
{
	g->player.target_dir.x = dx;
	g->player.target_dir.y = dy;
	if(g->key.scheme_change == 0)
	{
		g->player.target_plane.x = -dy * 0.66;
		g->player.target_plane.y = dx * 0.66;
	}
	else
	{
		g->player.target_plane.x = -dy * 0.33;
		g->player.target_plane.y = dx * 0.33;
	}
}

static const double	k_dir_vec[4][2] = {
	{0, -1},
	{-1, 0},
	{0, 1},
	{1, 0}
};

void	player_move(t_game *game, int dir)
{
	if (!can_move(game, dir))
		return ;
	game->player.facing = dir;
	set_player_target(game, k_dir_vec[dir][0], k_dir_vec[dir][1]);
}

void	player_turn(t_game *game, int turn_offset)
{
	int	new_dir;

	new_dir = ((game->player.facing + turn_offset) % 4 + 4) % 4;
	if(game->player.cycles < 0)
		game->player.cycles = 0;
	if(game->player.cycles)
	{
		game->player.cycles--;
		return;
	}
	if(!can_move(game, new_dir))
		return;
	game->player.cycles = 10;
	game->player.facing = new_dir;
	set_player_target(game, k_dir_vec[new_dir][0], k_dir_vec[new_dir][1]);
}

// void	player_move(t_game *game, int dir)
// {
// 	if (!can_move(game, dir))
// 		return ;
// 	if (dir == 0)
// 		set_player_target(game, 0, -1);
// 	else if (dir == 1)
// 		set_player_target(game, -1, 0);
// 	else if (dir == 2)
// 		set_player_target(game, 0, 1);
// 	else if (dir == 3)
// 		set_player_target(game, 1, 0);
// }

void	update_player_direction(t_game *game, double dt)
{
	double	speed;

	speed = 0.5 * dt;
	game->player.dir.x += (game->player.target_dir.x - game->player.dir.x)
		* speed;
	game->player.dir.y += (game->player.target_dir.y - game->player.dir.y)
		* speed;
	game->player.plane.x += (game->player.target_plane.x - game->player.plane.x)
		* speed;
	game->player.plane.y += (game->player.target_plane.y - game->player.plane.y)
		* speed;
}
