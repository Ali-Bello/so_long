/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 02:10:22 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/07 08:45:28 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	is_legal_move(char **map, int i, int j, t_game *game)
{
	if (map[i][j + 1] == '1')
		return (0);
	else if (map[i][j + 1] == 'C')
	{
		map[i][j + 1] = 'P';
		map[i][j] = '0';
		game->collected++;
		game->moves++;
	}
	else if (map[i][j + 1] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	else if (map[i][j + 1] == '0')
	{
		map[i][j + 1] = 'P';
		map[i][j] = '0';
		game->moves++;
	}
	return (1);
}

int	move_right(char **map, t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i] && !flag)
	{
		j = 0;
		while (map[i][j] && !flag)
		{
			if (map[i][j] == 'P')
				flag = 1;
			j++;
		}
		i++;
	}
	is_legal_move(map, --i, --j, game);
	return (0);
}

int	is_legal_move2(char **map, int i, int j, t_game *game)
{
	if (j > 0 && map[i][j - 1] == '1')
		return (0);
	else if (j > 0 && map[i][j - 1] == 'C')
	{
		map[i][j - 1] = 'P';
		map[i][j] = '0';
		game->collected++;
		game->moves++;
	}
	else if (j > 0 && map[i][j - 1] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	else if (j > 0 && map[i][j - 1] == '0')
	{
		map[i][j - 1] = 'P';
		map[i][j] = '0';
		game->moves++;
	}
	return (1);
}
int	move_left(char **map, t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i] && !flag)
	{
		j = 0;
		while (map[i][j] && !flag)
		{
			if (map[i][j] == 'P')
				flag = 1;
			j++;
		}
		i++;
	}
	is_legal_move2(map, --i, --j, game);
	return (0);
}

int	is_legal_move3(char **map, int i, int j, t_game *game)
{
	if (i > 0 && map[i - 1][j] == '1')
		return (0);
	else if (i > 0 && map[i - 1][j] == 'C')
	{
		map[i - 1][j] = 'P';
		map[i][j] = '0';
		game->collected++;
		game->moves++;
	}
	else if (i > 0 && map[i - 1][j] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	else if (i > 0 && map[i - 1][j] == '0')
	{
		map[i - 1][j] = 'P';
		map[i][j] = '0';
		game->moves++;
	}
	return (1);
}

int	move_up(char **map, t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i] && !flag)
	{
		j = 0;
		while (map[i][j] && !flag)
		{
			if (map[i][j] == 'P')
				flag = 1;
			j++;
		}
		i++;
	}
	is_legal_move3(map, --i, --j, game);
	return (0);
}

int	is_legal_move4(char **map, int i, int j, t_game *game)
{
	if (map[i + 1][j] == '1')
		return (0);
	else if (map[i + 1][j] == 'C')
	{
		map[i + 1][j] = 'P';
		map[i][j] = '0';
		game->collected++;
		game->moves++;
	}
	else if (map[i + 1][j] == 'E')
	{
		if (game->collected >= game->collectibles)
			exit(-1);
		game->moves++;
	}
	else if (map[i + 1][j] == '0')
	{
		map[i + 1][j] = 'P';
		map[i][j] = '0';
		game->moves++;
	}
	return (1);
}

int	move_down(char **map, t_game *game)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i] && !flag)
	{
		j = 0;
		while (map[i][j] && !flag)
		{
			if (map[i][j] == 'P')
				flag = 1;
			j++;
		}
		i++;
	}
	is_legal_move4(map, --i, --j, game);
	return (0);
}
