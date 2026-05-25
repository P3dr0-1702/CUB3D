/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:33:47 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/21 15:16:38 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Pac_Struct.h"
#include "map3D.h"

int	is_cub_file(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (path[len - 4] != '.')
		return (0);
	if (path[len - 3] != 'c')
		return (0);
	if (path[len - 2] != 'u')
		return (0);
	if (path[len - 1] != 'b')
		return (0);
	return (1);
}

static void	free_lines(char **lines, int size)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < size)
		free(lines[i++]);
	free(lines);
}

static int	count_lines(const char *path)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		return (-1);
	}
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

char	**map_read_file(const char *path)
{
	int		fd;
	int		line_count;
	int		i;
	char	**lines;

	line_count = count_lines(path);
	if (line_count <= 0)
		return (NULL);
	lines = ft_calloc((size_t)line_count + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror(path), free(lines), NULL);
	i = 0;
	while (i < line_count)
	{
		lines[i] = get_next_line(fd);
		if (!lines[i])
			return (close(fd), free_lines(lines, i), NULL);
		i++;
	}
	close(fd);
	lines[i] = NULL;
	return (lines);
}
