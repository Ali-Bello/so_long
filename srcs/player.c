/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:05:17 by aderraj           #+#    #+#             */
/*   Updated: 2024/06/29 01:07:48 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include <time.h>

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
void	draw_background(t_game *game)
{
	if (game->map[game->player->y][game->player->x] == '0')
		ft_cpy_img(game->assests[0]->animations->frames->img,
				game->bg, game->player->x * IMG_WIDTH, game->player->y * IMG_HEIGHT);
	if (game->map[game->player->y - 1][game->player->x] == '0')
		ft_cpy_img(game->assests[0]->animations->frames->img,
				game->bg, game->player->x * IMG_WIDTH, (game->player->y - 1) * IMG_HEIGHT);
	if (game->map[game->player->y + 1][game->player->x] == '0')
		ft_cpy_img(game->assests[0]->animations->frames->img,
				game->bg, game->player->x * IMG_WIDTH, (game->player->y + 1) * IMG_HEIGHT);
	if (game->map[game->player->y][game->player->x - 1] == '0')
		ft_cpy_img(game->assests[0]->animations->frames->img,
				game->bg, (game->player->x - 1) * IMG_WIDTH, game->player->y * IMG_HEIGHT);
	if (game->map[game->player->y][game->player->x + 1] == '0')
		ft_cpy_img(game->assests[0]->animations->frames->img,
				game->bg, (game->player->x + 1)* IMG_WIDTH, game->player->y * IMG_HEIGHT);
}
void	render_player(t_game *game)
{
	draw_background(game);
	ft_cpy_img(game->assests[0]->img, game->bg, game->player->target_x, game->player->target_y);
    if (!game->player->current_frame)
        game->player->current_frame = game->player->current_animation->frames;
    ft_cpy_img(game->player->current_frame->img,
            game->bg, game->player->x_px, game->player->y_px);
    game->player->current_frame = game->player->current_frame->next;
	if (game->player->x_px < game->player->target_x)
		game->player->x_px += STEP_SIZE;
	else if (game->player->x_px > game->player->target_x)
		game->player->x_px -= STEP_SIZE;
	if (game->player->y_px < game->player->target_y)
		game->player->y_px += STEP_SIZE;
	else if (game->player->y_px > game->player->target_y)
		game->player->y_px -= STEP_SIZE;
	if (game->player->x_px == game->player->target_x
		&& game->player->y_px == game->player->target_y)
		game->player_dir = -1;
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == '1')
		return ;
	else if (game->map[new_y][new_x] == 'C')
		game->collected++;
	else if (game->map[new_y][new_x] == 'E' && game->collected == game->collectibles)
		exit(-1);
	if (game->player_dir != -1)
	{
		game->player->init_x = game->player->x * IMG_WIDTH;
		game->player->init_y = game->player->y * IMG_HEIGHT;
	}
	set_positions(game, new_x, new_y);
    game->moves++;
	render_player(game);
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
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg->img_ptr, 0, 0);
	usleep(16670);
	return (0);
}
