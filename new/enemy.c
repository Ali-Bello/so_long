/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:54:00 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/17 01:47:49 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	set_available_space(t_game *game, char arr[][2], int *count)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '0')
			{
				arr[*count][0] = i;
				arr[*count][1] = j;
				(*count)++;
			}
			j++;
		}
		i++;
	}
	if (i <= 4)
		*count = 0;
}

void	spawn_enemy(t_game *game)
{
	char	available_positions[30 * 16][2];
	int		count;
	int		i;

	count = 0;
	set_available_space(game, available_positions, &count);
	if (count == 0)
	{
		game->enemy_flag = -1;
		return ;
	}
	srand(time(NULL));
	i = rand() % count;
	game->map[(int)available_positions[i][0]]
	[(int)available_positions[i][1]] = 'X';
}

void	move_enemy(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->enemy_data->x / TILE_SIZE;
	new_y = game->enemy_data->y / TILE_SIZE;
	srand(time(NULL));
	game->enemy_data->direction = rand() % 4 + 1;
	if (game->enemy_data->direction == 1)
		new_x++;
	else if (game->enemy_data->direction == 2)
		new_x--;
	else if (game->enemy_data->direction == 3)
		new_y++;
	else if (game->enemy_data->direction == 4)
		new_y--;
	if (new_x >= 0 && new_x < game->map_width && new_y >= 0
		&& new_y < game->map_height && game->map[new_y][new_x] != '1')
	{
		game->enemy_data->target_x = new_x * TILE_SIZE;
		game->enemy_data->target_y = new_y * TILE_SIZE;
	}
}

void	render_enemy(t_game *game)
{
	static int	delay;

	if (game->enemy_flag == -1)
		return ;
	game->enemy_data->animation_idx = get_animation_idx(game->enemy_data->\
	direction, 6);
	ft_cpy_img(game->enemy[game->enemy_data->animation_idx
		+ game->enemy_data->animation_frame], game->render_img,
		(game->enemy_data->x + game->enemy_data->step), (game->enemy_data->y
			+ game->enemy_data->step));
	if (delay++ % 4 == 0)
	{
		if (game->enemy_data->animation_frame == 5)
			game->enemy_data->animation_frame = 0;
		else
			game->enemy_data->animation_frame++;
	}
	move_enemy(game);
	if (game->enemy_flag == 0)
		return ;
	update_character(game->enemy_data, STEP_SIZE);
}
