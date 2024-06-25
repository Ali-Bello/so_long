/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:05:17 by aderraj           #+#    #+#             */
/*   Updated: 2024/06/12 09:39:18 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	get_player_mapxy(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] != 'P')
			j++;
		if (game->map[i][j] == 'P')
			break;
		i++;
	}
	game->player->x = j;
	game->player->y = i;
	game->player->x_px = j * IMG_WIDTH;
	game->player->y_px = i * IMG_HEIGHT;
	game->player->target_x = game->player->x_px;
	game->player->target_y = game->player->y_px;
}

void set_positions(t_game *game, int new_x, int new_y)
{
    if (game->player->x > new_x)
        game->player_dir = 0;
    else if (game->player->x < new_x)
        game->player_dir = 1;
    if (game->player->y > new_y)
        game->player_dir = 2;
    else if (game->player->y < new_y)
        game->player_dir = 3;
    game->map[new_y][new_x] = 'P';
    game->map[game->player->y][game->player->x] = '0';
    game->player->target_y = new_y * IMG_WIDTH;
    game->player->target_x = new_x * IMG_WIDTH;
    game->player->x = new_x;
    game->player->y = new_y;
}
void	move_to_closest_cell(t_game *game)
{
	if (game->move_delay < 2)
	{
		game->move_delay++;
		return ;
	}
	else
		game->move_delay = 0;
	render_player(game);
}
void	move_player(t_game *game, int new_x, int new_y)
{
	// if (game->player_dir != -1 && game->move_delay < 14)
	// {
	// 	game->move_delay++;
	// 	return ;
	// }
	// else if (game->player_dir != -1 && game->move_delay == 14)
	// 	game->move_delay = 0;
	if (game->map[new_y][new_x] == '1')
		return ;
	else if (game->map[new_y][new_x] == 'C')
		game->collected++;
	else if (game->map[new_y][new_x] == 'E' && game->collected == game->collectibles)
		exit(-1);
	if (game->player_dir != -1)
	{
		while (game->player->y_px != game->player->target_y)
			move_to_closest_cell(game);
		while (game->player->x_px != game->player->target_x)
			move_to_closest_cell(game);
	}
    set_positions(game, new_x, new_y);
    game->moves++;
}

t_animation *get_animation(t_game *game, int a_idx, int f_idx)
{
	t_animation	*tmp;
	int			i;

	tmp = game->assests[a_idx]->animations;
	i = 0;
	while (i < f_idx && tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void	draw_player(t_game *game)
{
	if (!game->player->current_frame)
		game->player->current_frame = game->player->current_animation->frames;
	ft_cpy_img(game->player->current_frame->img, game->bg, game->player->x_px, game->player->y_px);
	game->player->current_frame = game->player->current_frame->next;
}

void	render_player(t_game *game)
{
	if (!game->player->current_frame)
		game->player->current_frame = game->player->current_animation->frames;
	ft_cpy_img(game->player->current_frame->img, game->bg, game->player->x_px, game->player->y_px);
	game->player->current_frame = game->player->current_frame->next;
	if (!game->player_dir)
		game->player->x_px -= STEP_SIZE;
	else if (game->player_dir == 1)
		game->player->x_px += STEP_SIZE;
	else if (game->player_dir == 2)
		game->player->y_px -= STEP_SIZE;
	else if (game->player_dir == 3)
		game->player->y_px += STEP_SIZE;
	if (abs(game->player->target_x - game->player->x_px) < STEP_SIZE &&
		abs(game->player->target_y - game->player->y_px) < STEP_SIZE)
	{
		game->player->x_px = game->player->target_x;
		game->player->y_px = game->player->target_y;
		game->player->is_moving = 0;
		game->player_dir = -1;
	}
}

int	update_player(t_game *game)
{
	if (!game->player_dir)
		game->player->current_animation = get_animation(game, 4, 7);
	else if (game->player_dir == 1)
		game->player->current_animation = get_animation(game, 4, 19);
	else if (game->player_dir == 2)
		game->player->current_animation = get_animation(game, 4, 13);
	else if (game->player_dir == 3)
		game->player->current_animation = get_animation(game, 4, 1);
	else
		game->player->current_animation = game->assests[4]->animations;
	move_to_closest_cell(game);
	return (0);	
}
