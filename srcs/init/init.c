/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:20:03 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/23 11:48:38 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map3D.h"
#include "../player/player3D.h"
#include "../textures/textures3D.h"
#include "initializer.h"

void	init_assets(t_game *g)
{
	if (!g || !g->mlx_ptr)
		exit_game(EXIT_MLX, g, "init_assets() has not found a game");
	texture_load_cube(g);
	if (g->mode == MODE_PACMAN || g->mode == MODE_FREE_ROAM)
		texture_load_sprites(g);
	if (g->mode == MODE_PACMAN)
	{
		init_sprites(g);
		init_ghosts(g, 0);
	}
}

void	start_game_mode(t_game *g, t_mode mode)
{
	if (!g)
		return ;
	g->mode = mode;
	init_player(g, 0);
	init_base(g);
	set_lvl(g);
	init_assets(g);
	g->state = PLAY;
	g->timer.start_time = get_time_us();
	if (g->mode == MODE_CUBE || g->mode == MODE_FREE_ROAM)
	{
		g->key.mouse_hidden = 1;
		g->key.mouse_lock = 1;
		g->key.mouse_captured = 1;
		mlx_mouse_hide(g->mlx_ptr, g->win.win_ptr);
		center_mouse(g);
	}
	else
	{
		g->key.mouse_hidden = 0;
		g->key.mouse_lock = 0;
		g->key.mouse_captured = 0;
		mlx_mouse_show(g->mlx_ptr, g->win.win_ptr);
	}
}

static void	init_defaults(t_game *g)
{
	if (!g)
		return ;
	g->state = MENU;
	g->mode = MODE_CUBE;
	g->ray.hit_side = -1;
	g->player.target_map.x = -1;
	g->player.target_map.y = -1;
	g->player.collected_dots = 0;
	g->map.floor_color = -1;
	g->map.ceiling_color = -1;
	g->map.floor_path = NULL;
	g->map.ceiling_path = NULL;
	g->gate_passable = 0;
	g->level = 1;
	g->timer.mode_timer = 0;
	g->global_state = SCATTER;
	g->key.mouse_hidden = 0;
	g->key.mouse_lock = 0;
	g->key.mouse_captured = 0;
	g->key.show_raycast = 0;
}

void	init_execution(t_game *g)
{
	if (!g || !g->mlx_ptr || !g->win.win_ptr || !g->win.frame_buffer.img_ptr)
		exit_game(EXIT_MLX, g,
			"init_execution() has not found necessary pointers");
	g->ray.z_buffer = malloc(sizeof(double) * g->win.width);
	if (!g->ray.z_buffer)
		exit_game(EXIT_MALLOC, g,
			"init_execution() has failed to allocate memory E1");
	g->ray.sprite_z = malloc(sizeof(double) * g->win.width * g->win.height);
	if (!g->ray.sprite_z)
		exit_game(EXIT_MALLOC, g,
			"init_execution() had failed to allocate memory E2");
}

void	init(t_game *g, char *path)
{
	int		sprites;
	t_mode	detected_mode;

	if (!g)
		return ;
	init_defaults(g);
	g->map_path = path;
	detected_mode = detect_map_mode(g, path);
	g->mode = detected_mode;
	init_map(g, path);
	init_minilib(g);
	init_execution(g);
	sprites = init_spritesheet(g);
	if (g->debug_mode)
		ft_printf("Loaded %d sprites\n", sprites);
	if (detected_mode == MODE_CUBE)
	{
		start_game_mode(g, MODE_CUBE);
		return ;
	}
	init_menu(g);
}
