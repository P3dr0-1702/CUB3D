/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:18:06 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/23 11:47:20 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# define MOUSE_SENS 0.00035

typedef struct s_game	t_game;

typedef struct s_key
{
	int					w;
	int					a;
	int					s;
	int					d;
	int					left;
	int					right;
	int					up;
	int					down;
	int					esc;
	int					e;
	int					e_lock;
	int					mouse_lock;
	int					mouse_hidden;
	int					mouse_captured;
	int					show_raycast;
	int					k;
	int					controller_start;
}						t_key;

int						handle_close(t_game *g);
int						handle_key_press(int keycode, t_game *g);
int						handle_key_release(int keycode, t_game *g);
void					handle_gate_toggle(t_game *g);
int						handle_mouse_move(int x, int y, t_game *g);
void					center_mouse(t_game *g);
void					toggle_mouse_capture(t_game *g);

void					controller_player(t_game *game);

#endif
