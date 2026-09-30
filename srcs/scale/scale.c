/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro </var/spool/mail/pedro>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 13:56:37 by pedro             #+#    #+#             */
/*   Updated: 2026/09/30 14:22:23 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scale.h"

t_image scale_up(t_game game, t_image framebuffer)
{
	t_image bbuffer;
	t_point point;
	unsigned int color;
	point.x = -1;
	point.y = -1;

	bbuffer.img_ptr = mlx_new_image(game.mlx_ptr, framebuffer.width * 2, framebuffer.height * 2);
	bbuffer.img_addr = mlx_get_data_addr(bbuffer.img_ptr, &bbuffer.bpp, &bbuffer.l_len, &bbuffer.endian);
	bbuffer.width = framebuffer.width ;
	bbuffer.height = framebuffer.height ;
	while(++point.y < bbuffer.height)
	{
		point.x = -1;
		while(++point.x < bbuffer.width)
		{
			color = pixel_get(&framebuffer, point.x % 2, point.y % 2);
			if((color >>24) != 0xFF)
				ft_pixel_put(&bbuffer, point.x, point.y, color);
		}
		
	}
	return bbuffer;
}
