/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:40:08 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/21 15:16:07 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "map3D.h"

static int	find_map_start(t_game *g, char **file)
{
	int	i;

	i = 0;
	while (file && file[i])
	{
		if (map_is_map_line(g, file[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	find_map_end(t_game *g, char **file, int start)
{
	int	i;
	int	last;

	i = start;
	last = -1;
	while (file && file[i])
	{
		if (map_is_map_line(g, file[i]))
			last = i;
		else if (!map_is_empty_line(file[i]))
			break ;
		i++;
	}
	return (last);
}

static char	**extract_map(char **file_lines, int start, int end, t_game *g)
{
	t_point	counter;
	int		line_count;
	char	**map;

	if (!file_lines || start < 0 || end < start)
		return (NULL);
	line_count = end - start + 1;
	map = ft_calloc((size_t)line_count + 1, sizeof(char *));
	if (!map)
		return (free_2d((void **)file_lines), exit_game(EXIT_MALLOC, g,
				"extract_map(): unable allocate memory E1"), NULL);
	counter.x = start - 1;
	counter.y = -1;
	while (++counter.x <= end)
	{
		map[++counter.y] = ft_strdup(file_lines[counter.x]);
		if (!map[counter.y])
		{
			free_copy_partial(map, counter.y);
			return (free_2d((void **)file_lines), exit_game(EXIT_MALLOC, g,
					"Error Malloc"), NULL);
		}
	}
	map[counter.y + 1] = NULL;
	return (free_2d((void **)file_lines), map);
}

char	**load_map_from_cub(t_game *g, const char *path)
{
	char	**file_lines;
	int		start;
	int		end;
	char	**map;

	file_lines = map_read_file(path);
	if (!file_lines)
		exit_game(EXIT_MAP, g,
			"load_map_from_cub(): was unable to read file_lines");
	start = find_map_start(g, file_lines);
	if (start < 0)
		return (free_2d((void *)file_lines), exit_game(EXIT_MAP, g,
				"load_map_from_cub(): No map found"), NULL);
	end = find_map_end(g, file_lines, start);
	if (end < 0 || end > 255)
		return (free_2d((void *)file_lines), exit_game(EXIT_MAP, g,
				"load_map_from_cub(): Has found an invalid end"), NULL);
	if (g->debug_mode)
		ft_printf("Maps ends at line number %d\n", end);
	map = extract_map(file_lines, start, end, g);
	if (!map)
		exit_game(EXIT_MAP, g, "load_map_from_cub(): unable allocate memory");
	return (map);
}
