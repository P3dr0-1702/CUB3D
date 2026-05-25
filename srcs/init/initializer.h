/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:25:02 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/22 14:15:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZER_H
# define INITIALIZER_H
# include "../../Pac_Struct.h"

void	init_minilib(t_game *game);
void	init(t_game *g, char *path);
void	init_window(t_game *s);
void	init_assets(t_game *g);
void	init_ghosts(t_game *g, int is_death);
void	init_sprites(t_game *g);
void	init_execution(t_game *g);
void	init_menu(t_game *g);
void	init_base(t_game *s);
int		init_spritesheet(t_game *game);
int		controller_finder(char *argv);
bool	wrong_args(t_game *game, int ac, char **argv);
void	init_player(t_game *game, int is_death);
void	player_sprites(t_game *game);
int		init_map(t_game *g, const char *path);
void	map_validate_tiles(t_game *g);
void	ghost_info(int i, int *name, char *spawn);
t_point	find_spawn(char **map, char ghost);
int		init_dot_counter(t_ghost *gh);
void	set_lvl(t_game *game);
void	free_texture_paths(t_game *g);
t_mode	detect_map_mode(t_game *g, char *path);

#endif
