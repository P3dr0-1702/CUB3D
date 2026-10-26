/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_into_framebuffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:06:33 by pfreire-          #+#    #+#             */
/*   Updated: 2026/09/30 15:33:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render3D.h"

void	render_base_into_framebuffer(t_game *s)
{
	int				x;
	int				y;
	int				offset;
	unsigned int	color;

	y = 0;
	offset = 0;
	if(s->is_pacman_map)
		offset = 32 * s->scheme.scale_factor;
	while (y < s->base.height * s->scheme.scale_factor)
	{
		x = 0;
		while (x < s->base.width * s->scheme.scale_factor)
		{
			color = pixel_get(&s->base, x / s->scheme.scale_factor, y / s->scheme.scale_factor);
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&s->win.frame_buffer, ((x + (s->scheme.x_pos / 2) * s->scheme.scale_factor) - offset), ((y + (s->scheme.y_pos / 2) * s->scheme.scale_factor) - offset), color);
			x++;
		}
		y++;
	}
}



void	render_sprite_into_framebuffer(t_game *game, t_point coord,
		t_sprite_ref *sprite)
{
	t_point			point;
	unsigned int	color;

	point.y = 0;
	while (point.y < sprite->height * game->scheme.scale_factor)
	{
		point.x = 0;
		while (point.x < sprite->width * game->scheme.scale_factor)
		{
			color = pixel_get(&game->sprite_sheet.sprite_img, ((point.x
							/ game->scheme.scale_factor) + sprite->coord.x), ((point.y
							/ game->scheme.scale_factor) + sprite->coord.y));
			if ((color >> 24) != 0xFF)
				ft_pixel_put(&game->win.frame_buffer, ((point.x) + (coord.x
							- (game->scheme.x_pos / 2)) * game->scheme.scale_factor)
					% game->win.frame_buffer.width, ((point.y) + (coord.y
							- (game->scheme.y_pos / 2)) * game->scheme.scale_factor)
					% game->win.frame_buffer.height, color);
			point.x++;
		}
		point.y++;
	}
}

void	render_player(t_game *game, t_point coord)
{
	if ((game->player.target_dir.y) == 1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.down[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.x) == 1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.right[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.y) == -1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.up[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
	else if ((game->player.target_dir.x) == -1)
		render_sprite_into_framebuffer(game, coord,
			&game->player.frames.left[(game->player.pos.pixel_pos.x
				+ game->player.pos.pixel_pos.y) % 3]);
}

void	render_player_into_framebuffer(t_game *game)
{
	t_point	coord;

	coord.x = (((game->player.pos.tile_pos.x - 0.5) * TILE_SIZE) + game->scheme.x_pos) - 4;
	coord.y = (((game->player.pos.tile_pos.y - 0.5) * TILE_SIZE) + game->scheme.y_pos) - 4;
	game->player.pos.pixel_pos.x = coord.x;
	game->player.pos.pixel_pos.y = coord.y;
	render_player(game, coord);
}

void	render_into_framebuffer(t_game *game)
{
	render_base_into_framebuffer(game);
	render_pacdots_into_framebuffer(game);
	render_energizers_into_framebuffer(game);
	render_ghosts_into_framebuffer(game);
	render_player_into_framebuffer(game);
	if (game->debug_mode)
		render_debug_symbols(game);
}
