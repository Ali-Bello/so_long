/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:54:00 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/09 15:25:11 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

#define map_width game->map_width
#define map_height game->map_height

void    set_available_space(t_game *game, char arr[][2], int *count)
{
    int i;
    int j;

    i = 0;
    while (i < map_height)
    {
        j = 0;
        while (j < map_width)
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
    if (i <= 3)
        *count = 0;
}

void spawn_enemy(t_game *game)
{
    char    available_positions[map_width * map_height][2];
    int     count;
    int     i;

    count = 0;
    set_available_space(game, available_positions, &count);
    if (count == 0)
        return ;
    srand(time(NULL)); 
    i = rand() % count;
    game->map[(int)available_positions[i][0]]
            [(int)available_positions[i][1]] = 'X';
}

void    render_enemy(t_game *game)
{
    game->enemy_data->animation_idx = get_animation_idx(game->enemy_data->direction, 4);
    ft_cpy_img(game->floor, game->render_img, game->enemy_data->x + game->enemy_data->step,
                game->enemy_data->y + game->enemy_data->step);
    ft_cpy_img(game->enemy[game->enemy_data->animation_idx +
            game->enemy_data->animation_frame], game->render_img,
            (game->enemy_data->x + game->enemy_data->step),
            (game->enemy_data->y + game->enemy_data->step));
    if (game->enemy_data->animation_frame == 5)
        game->enemy_data->animation_frame = 0;
    else
        game->enemy_data->animation_frame++;
    if (game->enemy_data->step == TILE_SIZE)
    {
        game->enemy_data->step = 0;
        game->enemy_data->x = game->enemy_data->target_x;
        game->enemy_data->y = game->enemy_data->target_y;
    }
    else if (game->enemy_data->direction != 0)
        game->enemy_data->step += STEP_SIZE;
}