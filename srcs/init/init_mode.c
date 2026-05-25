/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 14:13:34 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/22 15:18:41 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map3D.h"
#include "../player/player3D.h"
#include "../textures/textures3D.h"
#include "initializer.h"

static int	is_pacman_identifier_items(char *p)
{
	if (!ft_strncmp(p, "PD", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "EN", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "ET", 2) && is_token_end(p[2]))
		return (1);
	if (!ft_strncmp(p, "SC", 2) && is_token_end(p[2]))
		return (1);
	return (0);
}

static int	is_pacman_identifier_ghosts(char *p)
{
	if (!ft_strncmp(p, "BL0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "BL1", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "PI0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "PI1", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "IN0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "IN1", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "CL0", 3) && is_token_end(p[3]))
		return (1);
	if (!ft_strncmp(p, "CL1", 3) && is_token_end(p[3]))
		return (1);
	return (0);
}

static int	is_pacman_identifier(char *p)
{
	p = skip_whitespace(p);
	if (is_pacman_identifier_items(p))
		return (1);
	if (is_pacman_identifier_ghosts(p))
		return (1);
	return (0);
}

t_mode	detect_map_mode(t_game *g, char *path)
{
	int		fd;
	char	*line;
	t_mode	mode;

	mode = MODE_CUBE;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		exit_game(EXIT_MAP, g, "Unable to open map file");
	}
	line = get_next_line(fd);
	while (line)
	{
		if (is_pacman_identifier(line))
			mode = MODE_PACMAN;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (mode);
}
