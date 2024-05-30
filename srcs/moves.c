/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:40:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/30 01:13:57 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	get_player_xy(t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (game->map[i] && !flag)
	{
		j = 0;
		while (game->map[i][j] && !flag)
		{
			if (game->map[i][j] == 'P')
				flag = 1;
			j++;
		}
		i++;
	}
	game->player->x = --j;
	game->player->y = --i;
}

void move_player(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] == '1')
		return;
    if (game->map[new_y][new_x] == 'C') {
        game->map[new_y][new_x] = 'P';
        game->map[game->player->y][game->player->x] = '0';
        game->collected++;
    } else if (game->map[new_y][new_x] == 'E') {
        if (game->collected >= game->collectibles) exit(0);
    } else if (game->map[new_y][new_x] == '0') {
		game->map[new_y][new_x] = 'P';
		game->map[game->player->y][game->player->x] = '0';
	}
	if (new_x < game->player->x)
		game->player_dir = 0;
	else if (new_x > game->player->x)
		game->player_dir = 1;
	if (new_y < game->player->y)
		game->player_dir = 2;
	else if (new_y > game->player->y)
		game->player_dir = 3;
	game->player->x = new_x;
	game->player->y = new_y;
    game->moves++;
}

