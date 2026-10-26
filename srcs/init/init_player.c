/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 16:03:48 by rmedeiro          #+#    #+#             */
/*   Updated: 2026/05/08 16:04:30 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Pac_Struct.h"
#include "initializer.h"

static const int	g_death_frames[12] = {
	225,
	227,
	228,
	229,
	230,
	231,
	236,
	237,
	238,
	239,
	239,
	241
};

void	player_sprites(t_game *game)
{
	int	i;

	game->player.frames.up[0] = game->sprite_sheet.sprites[213];
	game->player.frames.up[1] = game->sprite_sheet.sprites[212];
	game->player.frames.up[2] = game->sprite_sheet.sprites[252];
	game->player.frames.right[0] = game->sprite_sheet.sprites[242];
	game->player.frames.right[1] = game->sprite_sheet.sprites[232];
	game->player.frames.right[2] = game->sprite_sheet.sprites[252];
	game->player.frames.down[0] = game->sprite_sheet.sprites[243];
	game->player.frames.down[1] = game->sprite_sheet.sprites[233];
	game->player.frames.down[2] = game->sprite_sheet.sprites[252];
	game->player.frames.left[0] = game->sprite_sheet.sprites[211];
	game->player.frames.left[1] = game->sprite_sheet.sprites[210];
	game->player.frames.left[2] = game->sprite_sheet.sprites[252];
	i = 0;
	while (i < 12)
	{
		game->player.frames.death[i]
			= game->sprite_sheet.sprites[g_death_frames[i]];
		i++;
	}
}

void	init_player(t_game *game, int is_death)
{
	t_point	spawn_coord;

	if (!game || !game->map.grid)
		exit_game(EXIT_MAP, game, "init_player() invalid map pointers");
	spawn_coord = find_player_spawn(game);
	set_player_spawn(game, spawn_coord.x, spawn_coord.y,
		game->map.grid[spawn_coord.y][spawn_coord.x]);
	game->targets.player_spawn = spawn_coord;
	if (is_death)
		return ;
	player_sprites(game);
	change_pallete((t_point){.x = 2, .y = 1}, &game->player.frames);
	game->player.lives = 2;

}
