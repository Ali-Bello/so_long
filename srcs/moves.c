/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:40:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/28 23:28:02 by aderraj          ###   ########.fr       */
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

    game->player->x = new_x;
    game->player->y = new_y;
    game->moves++;
	//Start moving
}

void	right_move(t_game *game)
{
	int	flag;

	flag = 0;
	if (game->map[game->player->y][game->player->x + 1] != '1'
			&& (game->map[game->player->y][game->player->x + 1] == 'C'
			|| game->map[game->player->y][game->player->x + 1] == '0'))
	{
		game->map[game->player->y][game->player->x + 1] = 'P';
		game->map[game->player->y][game->player->x] = '0';
		if (game->map[game->player->y][game->player->x + 1] == 'C')
			game->collected++;
		game->moves++;
		flag = 1;

	}
	else if (game->map[game->player->y][game->player->x + 1] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	if (flag)
	{
		game->player->target_x = game->player->x + 1;
		game->player->target_y = game->player->y;
		game->player_dir = 1;
	}
}

void	left_move(t_game *game)
{
	int	flag;

	flag = 0;
	if (game->player->x > 0 && game->map[game->player->y][game->player->x - 1] != '1'
			&& (game->map[game->player->y][game->player->x - 1] == 'C'
			|| game->map[game->player->y][game->player->x - 1] == '0'))
	{
		game->map[game->player->y][game->player->x - 1] = 'P';
		game->map[game->player->y][game->player->x] = '0';
		if (game->map[game->player->y][game->player->x - 1] == 'C')
			game->collected++;
		game->moves++;
		flag = 1;


	}
	else if (game->player->x > 0 && game->map[game->player->y][game->player->x - 1] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	if (flag)
	{
		game->player->target_x = game->player->x - 1;
		game->player->target_y = game->player->y;
	}
}

void	up_move(t_game  *game)
{
	int	flag;

	flag = 0;
	if (game->player->y > 0 && game->map[game->player->y - 1][game->player->x] != '1'
		&& (game->map[game->player->y - 1][game->player->x] == 'C'
		|| game->map[game->player->y - 1][game->player->x] == '0'))
	{
		game->map[game->player->y - 1][game->player->x] = 'P';
		game->map[game->player->y][game->player->x] = '0';
		if (game->map[game->player->y - 1][game->player->x] == 'C')
			game->collected++;
		game->moves++;
		flag = 1;
	}
	else if (game->player->y > 0 && game->map[game->player->y - 1][game->player->x] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	if (flag)
	{
		game->player->target_x = game->player->x;
		game->player->target_y = game->player->y - 1;
	}
}

void	down_move(t_game *game)
{
	int	flag;

	flag = 0;
	if (game->map[game->player->y + 1][game->player->x] != '1'
		&& (game->map[game->player->y + 1][game->player->x] == 'C'
		|| game->map[game->player->y + 1][game->player->x] == '0'))
	{
		game->map[game->player->y + 1][game->player->x] = 'P';
		game->map[game->player->y][game->player->x] = '0';
		if (game->map[game->player->y + 1][game->player->x] == 'C')
			game->collected++;
		game->moves++;
		flag = 1;
	}
	else if (game->map[game->player->y + 1][game->player->x] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	if (flag)
	{
		game->player->target_x = game->player->x;
		game->player->target_y = game->player->y + 1;
	}
}
