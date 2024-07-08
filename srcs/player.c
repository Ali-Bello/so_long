/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:05:17 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/04 14:40:27 by aderraj          ###   ########.fr       */
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
            if (y == game->exit_y && x == game->exit_x) 
            {
				assetIndex = 3;
				ft_cpy_img(game->assests[0]->img, game->bg, x * IMG_WIDTH, y * IMG_HEIGHT);
			}
			// else if (y == game->player->y && x == game->player->x)
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
	render_enemy(game);
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
	game->map[new_y][new_x] = 'P';
	game->map[game->player->y][game->player->x] = '0';	
	game->player->x = new_x;
	game->player->y = new_y; 
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

void draw_enemy_background(t_game *game)
{
    static int prev_grid_x = -1, prev_grid_y = -1;
    int grid_x = game->enemy->x_px / IMG_WIDTH, grid_y = game->enemy->y_px / IMG_HEIGHT;
    int min_x = fmax(fmin(prev_grid_x, grid_x) - 1, 0);
    int max_x = fmin(fmax(prev_grid_x, grid_x) + 1, game->width / IMG_WIDTH - 1);
    int min_y = fmax(fmin(prev_grid_y, grid_y) - 1, 0);
    int max_y = fmin(fmax(prev_grid_y, grid_y) + 1, game->height / IMG_HEIGHT - 1);

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            int assetIndex = 0;
            if (y == game->exit_y && x == game->exit_x) 
            {
				assetIndex = 3;
				ft_cpy_img(game->assests[0]->img, game->bg, x * IMG_WIDTH, y * IMG_HEIGHT);
			}
			// else if (y == game->player->y && x == game->player->x)
			// 	continue;
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

void set_enemy_target(t_game *game) {
    int new_x, new_y;

    do {
        new_x = rand() % (game->width / IMG_WIDTH);
        new_y = rand() % (game->height / IMG_HEIGHT);
    } while (game->map[new_y][new_x] == '1'); // Ensure the new position is not a wall

    game->enemy->target_x = new_x * IMG_WIDTH;
    game->enemy->target_y = new_y * IMG_HEIGHT;
}

int is_valid_position(t_game *game, int x, int y) {
    return x >= 0 && x < game->width / IMG_WIDTH &&
           y >= 0 && y < game->height / IMG_HEIGHT &&
           game->map[y][x] != '1';
}

void move_enemy(t_game *game) {
    // Check if enemy has reached its target
    if (game->enemy->x_px == game->enemy->target_x && 
        game->enemy->y_px == game->enemy->target_y) 
    {
        set_enemy_target(game); // Set a new target position
    }

    // Determine the next step towards the target
    int next_x = game->enemy->x_px;
    int next_y = game->enemy->y_px;

    if (game->enemy->x_px < game->enemy->target_x)
        next_x += STEP_SIZE;
    else if (game->enemy->x_px > game->enemy->target_x)
        next_x -= STEP_SIZE;

    if (game->enemy->y_px < game->enemy->target_y)
        next_y += STEP_SIZE;
    else if (game->enemy->y_px > game->enemy->target_y)
        next_y -= STEP_SIZE;

    // Calculate grid positions
    int grid_x = next_x / IMG_WIDTH;
    int grid_y = next_y / IMG_HEIGHT;

    // Move enemy step by step towards the target if the next position is valid
    if (is_valid_position(game, grid_x, grid_y)) {
        game->enemy->x_px = next_x;
        game->enemy->y_px = next_y;
        game->enemy->x = grid_x;
        game->enemy->y = grid_y;
    } else {
        // If the next step is blocked, set a new target
        set_enemy_target(game);
    }
}

void render_enemy(t_game *game) {
    move_enemy(game);

    if (!game->enemy->current_animation->current_frame)
        game->enemy->current_animation->current_frame = game->enemy->current_animation->frames;
    if (game->enemy->current_animation->delay_counter < 5) {
        game->enemy->current_animation->delay_counter++;
        return;
    }
    game->enemy->current_animation->delay_counter = 0;
    draw_enemy_background(game);
    ft_cpy_img(game->enemy->current_animation->current_frame->img, game->bg,
               game->enemy->x_px, game->enemy->y_px);
    game->enemy->current_animation->current_frame = game->enemy->current_animation->current_frame->next;
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
	if (game->player->x_px == game->exit_x * IMG_WIDTH
		&& game->player->y_px == game->exit_y * IMG_HEIGHT
		&& game->collected == game->collectibles
		&& game->player_dir == -1)
	{
		printf("You won!\n");
		exit(0);
	}
	else if (game->player->x_px == game->enemy->x_px
		&& game->player->y_px == game->enemy->y_px)
	{
		printf("You lost!\n");
		exit(0);
	}
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->bg->img_ptr, 0, 0);
	usleep(16670);
	return (0);
}
