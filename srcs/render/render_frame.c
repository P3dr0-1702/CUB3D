/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:44:16 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/23 11:49:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "../draw/draw.h"
#include "../ghosts/ghosts.h"
#include "render3D.h"

void	clear_sprite_z(t_game *g)
{
	int	i;
	int	n;

	if (!g || !g->ray.sprite_z)
		return ;
	n = g->win.width * g->win.height;
	i = 0;
	while (i < n)
	{
		g->ray.sprite_z[i] = 1e30;
		i++;
	}
}

void	render_all_sprites(t_game *g)
{
	if (!g || !g->ray.z_buffer || !g->ray.sprite_z)
		return ;
	draw_pacdots(g);
	draw_energizers(g);
	draw_ghosts(g);
}

void	render_frame(t_game *game)
{
	if (!game)
		return ;
	if (game->key.esc)
		exit_game(EXIT_QUIT, game, NULL);
	player_controller(game);
	player_wrap_position(game);
	render_ceiling_texture(game);
	render_floor_texture(game);
	raycast_frame(game);
	handle_gate_toggle(game);
	clear_sprite_z(game);
	render_all_sprites(game);
	if (game->mode == MODE_PACMAN || game->mode == MODE_FREE_ROAM)
		render_into_framebuffer(game);
	if (game->key.show_raycast)
		render_raycast_debug(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win.win_ptr,
		game->win.frame_buffer.img_ptr, 0, 0);
}
