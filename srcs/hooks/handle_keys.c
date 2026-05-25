/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:59:32 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/23 13:10:39 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "hooks.h"

static int	handle_menu_key(int keycode, t_game *g)
{
	if (keycode == 65307)
		handle_close(g);
	else if (keycode == 49)
		start_game_mode(g, MODE_PACMAN);
	else if (keycode == 50)
		start_game_mode(g, MODE_FREE_ROAM);
	return (0);
}

static void	key_case_move(t_game *g, int keycode, int value)
{
	if (keycode == 65307)
		g->key.esc = value;
	else if (keycode == 119)
		g->key.w = value;
	else if (keycode == 97)
		g->key.a = value;
	else if (keycode == 115)
		g->key.s = value;
	else if (keycode == 100)
		g->key.d = value;
	else if (keycode == 65361)
		g->key.left = value;
	else if (keycode == 65363)
		g->key.right = value;
	else if (keycode == 65362)
		g->key.up = value;
	else if (keycode == 65364)
		g->key.down = value;
}

static void	key_case_toggle(t_game *g, int keycode, int value)
{
	if (keycode == 101 && (g->mode == MODE_CUBE
			|| g->mode == MODE_FREE_ROAM))
	{
		g->key.e = value;
		g->key.e_lock = 0;
	}
	else if (keycode == 109 && value == 1)
		toggle_mouse_capture(g);
	else if (keycode == 114 && value == 1)
		g->key.show_raycast = !g->key.show_raycast;
}

int	handle_key_press(int keycode, t_game *g)
{
	if (!g)
		return (0);
	if (g->state == MENU)
		return (handle_menu_key(keycode, g));
	key_case_move(g, keycode, 1);
	key_case_toggle(g, keycode, 1);
	return (0);
}

int	handle_key_release(int keycode, t_game *g)
{
	if (!g)
		return (0);
	if (keycode == 109 || keycode == 114)
		return (0);
	key_case_move(g, keycode, 0);
	key_case_toggle(g, keycode, 0);
	return (0);
}
