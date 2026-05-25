/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:43:18 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/22 14:10:11 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"

void	exit_game(int errcode, t_game *g, char *str)
{
	if (str)
		ft_dprintf(2, "\n%s\n", str);
	if (errcode == EXIT_QUIT)
		ft_dprintf(2, "\nQuitting Pac-Man...\n");
	else if (errcode == EXIT_MALLOC)
		ft_dprintf(2, "\nError: malloc failed\n");
	else if (errcode == EXIT_MLX)
		ft_dprintf(2, "\nError: MLX failed\n");
	else if (errcode == EXIT_MAP)
		ft_dprintf(2, "\nError: map parsing failed\n");
	else if (errcode == EXIT_INPUT)
		ft_dprintf(2, "\nError: invalid input\n");
	free_game(g);
	if (errcode == EXIT_QUIT)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

static void	free_pacman_arrays(t_game *g)
{
	int	i;

	if (!g)
		return ;
	if (g->pacdots)
	{
		free(g->pacdots);
		g->pacdots = NULL;
	}
	if (g->energizers)
	{
		free(g->energizers);
		g->energizers = NULL;
	}
	i = 0;
	while (i < 4)
	{
		if (g->ghosts[i].mental_map.grid)
		{
			free_2d((void *)g->ghosts[i].mental_map.grid);
			g->ghosts[i].mental_map.grid = NULL;
		}
		i++;
	}
}

void	free_game(t_game *g)
{
	int	i;

	if (!g)
		return ;
	free_raycast(g);
	free_pacman_arrays(g);
	if (g->map.grid)
		free_2d((void *)g->map.grid);
	g->map.grid = NULL;
	destroy_all_images(g);
	if (g->mlx_ptr && g->win.win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win.win_ptr);
	g->win.win_ptr = NULL;
	free_texture_paths(g);
	if (g->mlx_ptr)
	{
		mlx_destroy_display(g->mlx_ptr);
		free(g->mlx_ptr);
		g->mlx_ptr = NULL;
	}
	i = -1;
	while (++i < 4)
		free_2d((void **)g->ghosts[i].mental_map.grid);
	free(g);
}
