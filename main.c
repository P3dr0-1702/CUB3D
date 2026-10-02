/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 21:34:25 by pfreire-          #+#    #+#             */
/*   Updated: 2026/05/21 14:46:47 by pfreire-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/draw/draw.h"
#include "srcs/init/initializer.h"
#include "srcs/map/map3D.h"
#include "srcs/render/render3D.h"
#include "srcs/textures/textures3D.h"
#include "srcs/utils/helpers.h"

uint32_t	hash_file(const char *path)
{
	int				fd;
	ssize_t			read_bytes;
	unsigned char	buf[256];
	uint32_t		hash;
	ssize_t			i;

	hash = 2166136261u;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	read_bytes = read(fd, buf, sizeof(buf));
	while (read_bytes > 0)
	{
		i = 0;
		while (i < read_bytes)
		{
			hash ^= buf[i];
			hash *= 166777619u;
			i++;
		}
		read_bytes = read(fd, buf, sizeof(buf));
	}
	close(fd);
	return (hash);
}

void	reset_game(t_game *game, int is_death)
{
	int	i;

	if(game->state != MENU)
		sleep(2);
	if (game->mode == MODE_CUBE)
		return ;
	if (is_death)
		game->player.lives--;
	init_player(game, 1);
	init_ghosts(game, 1);
	if (is_death)
		return ;
	i = -1;
	while (++i < game->pacdot_count)
		game->pacdots[i].active = true;
	i = -1;
	while (++i < game->energizer_count)
		game->energizers[i].active = true;
	if(game->state != MENU)
		game->level++;
	if (game->level > 255)
		segfault_func(game);
	game->player.collected_dots = 0;
}

int	gameloop(t_game *game)
{
	long	now;

	controller_player(game);
	now = get_time_us();
	if (game->timer.last_time_up == 0)
	{
		game->timer.last_time_up = now;
		return (0);
	}
	if (now - game->timer.last_time_up < UPDATE_F)
		return (0);
	game->timer.last_time_up = now;
	if (is_time_up(game, now))
	{
		game->timer.mode++;
		game->global_state = change_game_mode(game);
		game->timer.mode_time_start = now;
	}
	if (game->state == MENU)
		return (game->timer.mode_time_start = now, draw_menu(game), 0);
	return (render_frame(game), 0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if ((ac > 4 || ac < 2))
		return (print_usage(), -1);
	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		exit_game(EXIT_MALLOC, NULL, "main() failed to allocate game");
	if (wrong_args(game, ac, av) && print_usage())
		exit_game(EXIT_FAILURE, game, "Wrong Args");
	if(hash_file(av[1]) == 2274426481)
		game->is_pacman_map = true;
	if(game->is_pacman_map)
		printf("PACCCCCCCCCCCCMANNNN\n");
	init(game, av[1]);
	mlx_hook(game->win.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->win.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win.win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->win.win_ptr, 17, 0, handle_close, game);
	mlx_loop_hook(game->mlx_ptr, gameloop, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
