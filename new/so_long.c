/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:44:16 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 02:44:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int key_down(int keycode, t_game *game)
{
    if (keycode == 65307)
		error_prompts(game);
	else if (keycode == 100)
		move_player(game, (game->player_data->x / TILE_SIZE) + 1,
            game->player_data->y / TILE_SIZE);
	else if (keycode == 115)
		move_player(game, game->player_data->x / TILE_SIZE,
            (game->player_data->y / TILE_SIZE) + 1);
	else if (keycode == 97)
		move_player(game, (game->player_data->x / TILE_SIZE) - 1,
            game->player_data->y / TILE_SIZE);
	else if (keycode == 119)
		move_player(game, game->player_data->x / TILE_SIZE,
            (game->player_data->y / TILE_SIZE - 1));
	return (0);
}

int key_up(int keycode, t_game *game)
{
    if (keycode == 100 || keycode == 115 || keycode == 97 || keycode == 119)
    {
        game->player_data->direction = 0;
        game->player_data->step = TILE_SIZE;
    }
    return (0);
}

int main(int ac, char **av)
{
    t_game  game;

    if (ac != 2)
        return (0);
    game_init(&game, av[1]);
    if (game.error_code != 0)
        return (error_prompts(&game));
    mlx_hook(game.win, 2, 1L << 0, key_down, &game);
    // mlx_hook(game.win, 3, 1L << 1, key_up, &game);
    mlx_loop_hook(game.mlx, render_game, &game);
    mlx_loop(game.mlx);
    return (0);
}
