/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:48:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/21 16:21:28 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP3D_H
# define MAP3D_H

# define TILE_WALL 1
# define TILE_VOID 2
# define TILE_SOLID 3
# define TILE_WALKABLE 4

typedef struct s_game	t_game;
typedef struct s_ghost	t_ghost;

typedef struct s_map
{
	char				**grid;
	int					width;
	int					height;
	int					ceiling_color;
	int					floor_color;
	char				*floor_path;
	char				*ceiling_path;
}						t_map;

char					**load_map_from_cub(t_game *g, const char *path);
void					map_validate_bounds(t_game *g);
int						map_is_map_line(t_game *g, char *line);
int						map_is_empty_line(char *s);
int						map_row_last_col(t_game *g, int row, int want_wrap);
char					map_get_tile(t_game *game, int row, int col, int wrap);
int						map_tile_type(char t, int tile_type);
char					**map_read_file(const char *path);
int						map_is_wrap_tile(t_game *g, int row, int col);
void					player_wrap_position(t_game *g);
void					ghost_wrap_position(t_game *g, t_ghost *ghost);
double					get_sprite_wrap_offset_x(t_game *g, double sprite_x,
							double sprite_y);
int						is_whitespace(char c);
char					**copy_map(char **map_grid);
int						is_token_end(char c);
int						map_is_config_line(t_game *g, char *line);
void					map_validate_bounds(t_game *g);
int						is_cub_file(const char *path);
void					map_validate_wrap_portals(t_game *game);
double					wrap_value(double x, double width);
void					flood_fill(char **map, int x, int y);
int						map_is_cub_prefix(char *p);
int						map_pacman_mode_prefix(char *p);
int						map_pacman_mode_prefix_helper(char *p);
int						map_cube_mode_prefix(char *p);
void					free_copy_partial(char **map_copy, int rows_done);

#endif
