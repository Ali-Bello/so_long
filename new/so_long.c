/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:44:16 by marvin            #+#    #+#             */
/*   Updated: 2024/07/17 02:48:40 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
	map = NULL;
}

int	key_down(int keycode, t_game *game)
{
	if (keycode == 65307)
		error_prompts(game);
	else if (keycode == 100 || keycode == 65363)
		move_player(game, (game->player_data->x / TILE_SIZE) + 1,
			(game->player_data->y / TILE_SIZE));
	else if (keycode == 115 || keycode == 65364)
		move_player(game, (game->player_data->x / TILE_SIZE),
			(game->player_data->y / TILE_SIZE) + 1);
	else if (keycode == 97 || keycode == 65361)
		move_player(game, (game->player_data->x / TILE_SIZE) - 1,
			(game->player_data->y / TILE_SIZE));
	else if (keycode == 119 || keycode == 65362)
		move_player(game, (game->player_data->x / TILE_SIZE),
			(game->player_data->y / TILE_SIZE) - 1);
	return (0);
}

int	x_button(t_game *game)
{
	error_prompts(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_putstr_fd("Error\nARGUMENTS : -->\
		[arguments are different than 2]\n", 1), 0);
	game_init(&game, av[1]);
	if (game.error_code != 0)
		return (error_prompts(&game));
	mlx_key_hook(game.win, key_down, &game);
	mlx_hook(game.win, 17, 0, x_button, &game);
	mlx_loop_hook(game.mlx, render_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
