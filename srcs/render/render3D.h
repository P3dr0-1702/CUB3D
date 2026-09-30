/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 23:43:38 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/09/30 15:32:50 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER3D_H
# define RENDER3D_H

# include "../../Pac_Struct.h"
# include "../scale/scale.h"

# define TILE_SIZE_3D 1
# define SPR_PACDOT 1
# define SPR_ENERGIZER 2
# define SPR_GHOST 3

# define CEILING_DIST 2.8
# define CEILING_HORIZON 40.0
# define CEILING_MIN_SCREEN_DIST 6.0
# define CEILING_CENTER_MARGIN 2

# define FLOOR_START_OFFSET 2
# define FLOOR_MIN_DIST 4.0

# define X_POS 728
# define Y_POS 320


typedef struct s_game	t_game;
typedef struct s_image	t_image;
typedef struct s_ghost	t_ghost;

void					set_plane(t_game *g, t_fc *plane, double dist);
void					render_debug_symbols(t_game *game);
void					render_into_framebuffer(t_game *game);
int						raycast_find_wall(t_game *g);
void					ray_perp_wall_distance(t_game *g);
void					ray_draw_range(t_game *g);
void					ray_init_steps(t_game *g);
void					ray_init(t_game *g, int col);
void					raycast_frame(t_game *g);
void					render_targets(t_game *game);
void					render_debug_symbols(t_game *game);
void					clear_sprite_z(t_game *g);
void					render_all_sprites(t_game *g);
void					render_frame(t_game *game);
void					render_base_into_framebuffer(t_game *s);
void					render_sprite_into_framebuffer(t_game *game,
							t_point coord, t_sprite_ref *sprite);
void					render_normal_ghost(t_game *game, t_point coord,
							t_ghost *ghost);
void					render_eaten_ghost(t_game *game, t_point coord,
							t_ghost *ghost);
void					render_elroy_cruiser(t_game *game, t_point coord,
							t_ghost *ghost);
void					render_ghost_into_framebuffer(t_game *game,
							t_point coord, t_ghost *ghost);
void					render_ghosts_into_framebuffer(t_game *game);
void					render_player(t_game *game, t_point coord);
void					render_player_into_framebuffer(t_game *game);
void					render_pacdots_into_framebuffer(t_game *game);
void					render_energizers_into_framebuffer(t_game *game);
void					render_into_framebuffer(t_game *game);
void					render_floor_texture(t_game *g);
void					render_ceiling_texture(t_game *g);
void					render_raycast_debug(t_game *g);

#endif
