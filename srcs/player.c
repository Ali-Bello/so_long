/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:05:17 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/01 04:26:38 by aderraj          ###   ########.fr       */
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
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				game->player->x = j;
				game->player->y = i;
			}
			else if (game->map[i][j] == 'C')
				game->collectibles++;
			j++;
		}
		i++;
	}
	game->player->x_px = game->player->x * IMG_WIDTH;
	game->player->y_px = game->player->y * IMG_HEIGHT;
	game->player->target_x = game->player->x_px;
	game->player->target_y = game->player->y_px;
}


void draw_background(t_game *game)
{
    static int prev_grid_x = -1, prev_grid_y = -1;
    int grid_x = game->player->x_px / IMG_WIDTH, grid_y = game->player->y_px / IMG_HEIGHT;

    int min_x = fmax(fmin(prev_grid_x, grid_x) - 1, 0);
    int max_x = fmin(fmax(prev_grid_x, grid_x) + 1, game->width / IMG_WIDTH - 1);
    int min_y = fmax(fmin(prev_grid_y, grid_y) - 1, 0);
    int max_y = fmin(fmax(prev_grid_y, grid_y) + 1, game->height / IMG_HEIGHT - 1);

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            int assetIndex = 0;
            if (game->map[y][x] == 'E') 
            {
				assetIndex = 3;
				ft_cpy_img(game->assests[0]->img, game->bg, x * IMG_WIDTH, y * IMG_HEIGHT);
			}
			else if (game->map[y][x] == '1') assetIndex = 1;
			else if (game->map[y][x] == 'C')
			{
				ft_cpy_img(game->assests[0]->img, game->bg, x * IMG_WIDTH, y * IMG_HEIGHT);
				assetIndex = 2;
			}
            ft_cpy_img(game->assests[assetIndex]->animations->frames->img, game->bg, x * IMG_WIDTH, y * IMG_HEIGHT);
        }
    }
    prev_grid_x = grid_x;
    prev_grid_y = grid_y;
}


void	render_player(t_game *game)
{
	draw_background(game);
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
	game->player->target_y = new_y * IMG_WIDTH;
    game->player->target_x = new_x * IMG_WIDTH;
	if (game->map[new_y][new_x] == 'E')
		game->map[new_y][new_x] = 'E';
	else
		game->map[new_y][new_x] = 'P';
    if (game->map[game->player->y][game->player->x] == 'E')
		game->map[game->player->y][game->player->x] = 'E';
	else
		game->map[game->player->y][game->player->x] = '0';	
	game->player->x = new_x;
	game->player->y = new_y; 
}

void	move_player(t_game *game, int new_x, int new_y)
{
	printf("player->x = %d, player->y = %d\n", game->player->x, game->player->y);
	printf("map[player->y][player->x] = %c\n", game->map[game->player->y][game->player->x]);
	if (game->map[new_y][new_x] == '1')
		return ;
	else if (game->map[new_y][new_x] == 'C')
		game->collected++;
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
	if (game->map[game->player->y_px / IMG_WIDTH][game->player->x_px / IMG_HEIGHT] == 'E' && game->collected == game->collectibles)
		exit(-1);
	usleep(16670);
	return (0);
}
