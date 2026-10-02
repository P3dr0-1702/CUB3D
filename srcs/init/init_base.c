/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:04:01 by pfreire-          #+#    #+#             */
/*   Updated: 2026/04/23 14:43:12 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../base/base.h"
#include "../utils/helpers.h"
#include "initializer.h"

void	init_base(t_game *s)
{
	int				tile;
	t_point			point;
	unsigned int	color;
	int offsetx;

	offsetx = 0;
	color = 0;
	point.x = -1;
	point.y = -1;
	s->base.img_ptr = mlx_new_image(s->mlx_ptr, s->win.width, s->win.height);
	s->base.img_addr = mlx_get_data_addr(s->base.img_ptr, &s->base.bpp,
			&s->base.l_len, &s->base.endian);
	if(s->is_pacman_map)
	{
		// s->base.width = (s->map.width * TILE_SIZE) + 98;
		s->base.width = (s->map.width * TILE_SIZE);
		s->base.height = (s->map.height) * TILE_SIZE;
	}
	else
	{
		s->base.width = (s->map.width * TILE_SIZE);
		s->base.height = (s->map.height) * TILE_SIZE;
	}
	if(s->is_pacman_map)
	{
		printf("PACMMAAAAAAAAAAAA");
		offsetx = 0;
	}
	while (++point.y < s->map.height)
	{
		point.x = -1;
		while (++point.x < (s->map.width))
		{
			tile = which_tile(s->map.grid, &s->map, point, s->debug_mode);
			if (tile == -1)
				exit_game(EXIT_MALLOC, s,
					"init_base(): Something when very wrong in tile selection");
			put_tile_inbase(s, tile, color, (t_point){.y = point.y, .x = point.x + offsetx});
		}
	}
}
