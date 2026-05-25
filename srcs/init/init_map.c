/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 22:12:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/21 16:18:15 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../render/render3D.h"
#include "../textures/textures3D.h"
#include "initializer.h"

static int	init_game_grid(t_game *game, char **temp)
{
	int	i;

	game->map.grid = ft_calloc(sizeof(char *), game->map.height + 1);
	if (!game->map.grid)
		return (free_2d((void **)temp), -1);
	i = 0;
	while (temp && temp[i])
	{
		game->map.grid[i] = ft_calloc(sizeof(char), game->map.width + 1);
		if (!game->map.grid[i])
			return (free_2d((void **)temp), -1);
		ft_memcpy(game->map.grid[i], temp[i], ft_strlen(temp[i]));
		i++;
	}
	return (free_2d((void **)temp), 0);
}

static void	san(char **temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!temp)
		return ;
	while (temp[j])
	{
		i = 0;
		while (temp[j][i])
		{
			if (temp[j][i] == '\n' && !temp[j][i + 1])
				temp[j][i] = '\0';
			i++;
		}
		j++;
	}
}

static int	map_is_valid_tile(t_game *g, char c)
{
	if (c == '\0')
		return (0);
	if (c == '\n')
		return (1);
	if (c == WALL || c == OPEN_SPACE || c == VOID || c == 'M')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (g->mode == MODE_PACMAN)
	{
		if (c == PACDOT || c == ENERGIZER || c == WRAP_PORTS || c == BLINKY_T
			|| c == PINKY_T || c == INKY_T || c == CLYDE_T || c == GATE
			|| c == PLAYER)
			return (1);
	}
	return (0);
}

void	map_validate_tiles(t_game *g)
{
	int		y;
	int		x;
	char	tile;

	if (!g || !g->map.grid)
		exit_game(EXIT_MAP, g, "map_validate_tiles: missing grid");
	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			tile = g->map.grid[y][x];
			if (!map_is_valid_tile(g, tile))
				exit_game(EXIT_MAP, g, "map_validate_tiles: invalid tile");
			x++;
		}
		y++;
	}
}

int	init_map(t_game *g, const char *path)
{
	char	**temp;

	if (!is_cub_file(path))
		exit_game(EXIT_MAP, g, "Invalid file extension: expected .cub");
	parse_texture_path(g, path);
	if (g->map.grid)
		free_2d((void *)g->map.grid);
	temp = load_map_from_cub(g, path);
	san(temp);
	if (!temp)
		exit_game(EXIT_MAP, g, "parse() has not found a grid");
	g->map.height = ytile(temp);
	g->map.width = xtile(temp);
	if (g->map.height > 200 || g->map.width > 255 || g->map.width
		* g->map.height > 16256)
		return (free_2d((void **)temp), exit_game(EXIT_MAP, g,
				"Map is too big"), -1);
	if (init_game_grid(g, temp))
		exit_game(EXIT_MALLOC, g, "Something broke");
	if (g->debug_mode)
		return (0);
	map_validate_tiles(g);
	map_validate_wrap_portals(g);
	map_validate_bounds(g);
	return (0);
}
