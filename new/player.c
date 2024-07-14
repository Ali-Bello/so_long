/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:58:07 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/09 13:31:50 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int move_player(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] == '1')
        return (0);
    else if (game->map[new_y][new_x] == 'C')
        game->collectibles_count--;
    if (new_x * TILE_SIZE > game->player_data->x)
        game->player_data->direction = 1;
    else if (new_x * TILE_SIZE < game->player_data->x)
        game->player_data->direction = 2;
    else if (new_y * TILE_SIZE > game->player_data->y)
        game->player_data->direction = 3;
    else if (new_y * TILE_SIZE < game->player_data->y)
        game->player_data->direction = 4;
    game->player_data->prev_x = game->player_data->x / TILE_SIZE;
    game->player_data->prev_y = game->player_data->y / TILE_SIZE;
    game->player_data->target_x = new_x * TILE_SIZE;
    game->player_data->target_y = new_y * TILE_SIZE;
    game->moves_count++;

    return (1);
}

void update_player(t_game *game)
{
    printf("player_dir: %d\n", game->player_data->direction);
    if (game->player_data->x < game->player_data->target_x)
        game->player_data->x += STEP_SIZE;
    if (game->player_data->x > game->player_data->target_x)
        game->player_data->x -= STEP_SIZE;
    if (game->player_data->y < game->player_data->target_y)
        game->player_data->y += STEP_SIZE;
    if (game->player_data->y > game->player_data->target_y)
        game->player_data->y -= STEP_SIZE;
    printf("player_x: %d, player_y: %d\n", game->player_data->x, game->player_data->y);
    printf("player_target_x: %d, player_target_y: %d\n", game->player_data->target_x, game->player_data->target_y);
    if (game->player_data->x == game->player_data->target_x
        && game->player_data->y == game->player_data->target_y)
    {
        game->map[game->player_data->prev_y][game->player_data->prev_x] = '0';
        game->map[game->player_data->y / TILE_SIZE][game->player_data->x / TILE_SIZE] = 'P';
        game->player_data->direction = 0;
    }
}


void    render_player(t_game *game)
{
    game->player_data->animation_idx = get_animation_idx(game->player_data->direction, 6);
    ft_cpy_img(game->player[game->player_data->animation_idx + game->player_data->animation_frame],
        game->render_img, game->player_data->x, game->player_data->y);
    update_player(game);
    if (game->player_data->animation_frame == 5)
        game->player_data->animation_frame = 0;
    else
        game->player_data->animation_frame++;
}
