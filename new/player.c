/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:58:07 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/09 00:07:15 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int move_player(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] == '1')
        return (0);
    else if (game->map[new_y][new_x] == 'C')
        game->collectibles_count--;
    game->map[new_y][new_x] = 'P';
    game->map[game->player_data->y][game->player_data->x] = '0';
    game->player_data->target_x = new_x * TILE_SIZE;
    game->player_data->target_y = new_y * TILE_SIZE;
    return (1);
}

void render_player(t_game *game)
{
    game->player_data->animation_idx = get_animation_idx(game->player_data->direction);
    ft_cpy_img(game->player[game->player_data->animation_idx +
            game->player_data->animation_frame], game->render_img,
            (game->player_data->x + game->player_data->step) * TILE_SIZE,
            (game->player_data->y + game->player_data->step)* TILE_SIZE);

    if (game->player_data->animation_frame == 5)
        game->player_data->animation_frame = 0;
    else
        game->player_data->animation_frame++;
    if (game->player_data->step == TILE_SIZE)
    {
        game->player_data->step = 0;
        game->player_data->x = game->player_data->target_x;
        game->player_data->y = game->player_data->target_y;
    }
    else
        game->player_data->step += STEP_SIZE;
}