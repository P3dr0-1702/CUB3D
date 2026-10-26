/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:11:27 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/14 22:55:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "player3D.h"

static int	set_player_orientation(t_game *g, char c)
{
	if (c == 'N')
	{
		g->player.dir.x = 0;
		g->player.dir.y = -1;
		g->player.plane.x = 0.66;
		g->player.plane.y = 0;
		return 0;
	}
	else if (c == 'S')
	{
		g->player.dir.x = 0;
		g->player.dir.y = 1;
		g->player.plane.x = -0.66;
		g->player.plane.y = 0;
		return 2;
	}
	else if (c == 'E')
	{
		g->player.dir.x = 1;
		g->player.dir.y = 0;
		g->player.plane.x = 0;
		g->player.plane.y = 0.66;
		return 1;
	}
	else if (c == 'W')
	{
		g->player.dir.x = -1;
		g->player.dir.y = 0;
		g->player.plane.x = 0;
		g->player.plane.y = -0.66;
		return 3;
	}
	return 0;
}


void	set_player_spawn(t_game *game, int col, int row, char dir)
{
	if (game->map.grid[row][col] == VOID)
		exit_game(EXIT_MAP, game, "set_player_spawn(): player in VOID tile");
	if (map_get_tile(game, row, col + 1, 0) == VOID
		|| map_get_tile(game, row, col - 1, 0) == VOID
		|| map_get_tile(game, row + 1, col, 0) == VOID
		|| map_get_tile(game, row - 1, col, 0) == VOID)
		exit_game(EXIT_MAP, game, "set_player_spawn(): player next VOID tile");
	game->player.pos.tile_pos.x = (double)col + 0.5;
	game->player.pos.tile_pos.y = (double)row + 0.5;
	game->player.pos.pixel_pos.x = col * TILE_SIZE;
	game->player.pos.pixel_pos.y = row * TILE_SIZE;
	game->player.facing = set_player_orientation(game, dir);
	game->player.target_dir = game->player.dir;
	game->player.target_plane = game->player.plane;
	
}

static int	is_player_spawn(char tile)
{
	return (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W');
}

t_point	find_player_spawn(t_game *game)
{
	int		y;
	int		x;
	int		found;
	t_point	spawn;

	found = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (is_player_spawn(game->map.grid[y][x]))
			{
				if (found)
					exit_game(EXIT_MAP, game, "More than one player");
				found = 1;
				spawn.x = x;
				spawn.y = y;
			}
		}
	}
	if (!found)
		exit_game(EXIT_MAP, game, "E404: has not found a player");
	return (spawn);
}
