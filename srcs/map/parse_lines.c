/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 22:38:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/23 11:12:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../textures/textures3D.h"
#include "map3D.h"

bool	target_tile(char c)
{
	if (c == 'L' || c == 'V' || c == 'K' || c == 'Y')
		return (true);
	return (false);
}

static int	map_is_valid_char_in_line(char c, t_mode mode)
{
	if (c == '\n' || c == ' ' || c == '\t' || c == WALL || c == OPEN_SPACE
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (mode == MODE_PACMAN || mode == MODE_FREE_ROAM)
	{
		if (c == PACDOT || c == WRAP_PORTS || c == ENERGIZER || c == BLINKY_T
			|| c == PINKY_T || c == INKY_T || c == CLYDE_T || c == GATE
			|| c == PLAYER || c == 'M')
			return (1);
	}
	return (0);
}

int	map_is_map_line(t_game *g, char *line)
{
	char	*p;
	int		has_tile;

	if (!line || !g)
		return (0);
	p = skip_whitespace(line);
	if (!*p || *p == '\n' || map_is_cub_prefix(p))
		return (0);
	has_tile = 0;
	while (*p && *p != '\n')
	{
		if (*p != ' ' && *p != '\t')
		{
			if (!map_is_valid_char_in_line(*p, g->mode))
				return (0);
			has_tile = 1;
		}
		p++;
	}
	return (has_tile);
}

int	map_is_config_line(t_game *g, char *line)
{
	char	*p;

	if (!line || !g)
		return (0);
	p = skip_whitespace(line);
	return (map_is_cub_prefix(p));
}
