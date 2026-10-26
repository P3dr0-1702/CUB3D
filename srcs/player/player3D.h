/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 23:09:31 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 18:42:13 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER3D_H
# define PLAYER3D_H

# include <stdbool.h>

# define PLAYER_SPEED 0.12
# define ROT_SPEED 0.06
# define PLAYER_RADIUS 0.18

typedef struct s_game	t_game;
typedef struct s_point	t_point;

typedef enum e_player_action
{
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT
}						t_player_action;

t_point					find_player_spawn(t_game *game);
void					player_apply_action(t_game *g, t_player_action act);
void					player_rotate(t_game *g, double angle);
void					apply_player_movement(t_game *g, double dx, double dy);
bool					player_collect_energizer(t_game *g);
bool					player_collect_pacdots(t_game *g);
int						player_hits_wall(t_game *g, int row, int col);
int						ghost_hits_wall(t_game *g, int row, int col);
void					player_collision(t_game *g);
void					player_controller(t_game *g);
bool					can_move(t_game *game, int dir);
void					player_move(t_game *game, int dir);
void					update_player_direction(t_game *game, double dt);
void					set_player_spawn(t_game *game, int col, int row,
							char dir);
int						player_touched_ghost(t_game *g);
void					handle_ghost_touch(t_game *g);
void					play_death(t_game *game, t_point coord);
void					player_turn(t_game *game, int turn_offset);

#endif
