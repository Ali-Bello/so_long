/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 04:40:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 04:40:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    set_available_space(t_game *game, char **arr, int *count)
{
    int i;
    int j;

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
    if (i <= 3)
        *count = 0;
}

void    spawn_enemy(t_game *game)
{
    char    available_positions[game->map_height * game->map_width][2];
    int     count;
    int     tmp;

    set_available_space(game, available_positions, &count);
    if (count == 0)
        return;
    srand(time(NULL)); 
    tmp = rand() % count;
    game->map[(int)available_positions[tmp][0]]
            [(int)available_positions[tmp][1]] = 'X';
}

void    character_init(t_character *character, char c, char **map)
{
    get_position(c, map, &character->y, &character->x);
    character->x *= TILE_SIZE;
    character->y *= TILE_SIZE;
    character->target_x = character->x;
    character->target_y = character->y;
    character->direction = 0;
}

void    game_init(t_game *game, char *path)
{
    game->error_code = 0;
    game_allocs(game);
    game->map = read_map(path, game);
    if (game->error_code)
        return ;
    game->map_width = ft_strlen(game->map[0]);
    game->map_height = get_height(game->map);
    game->mlx = mlx_init();
    if (!game->mlx)
        return ;
    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, 
                                game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
        return ;
    load_assets(game);
    spawn_enemy(game);
    character_init(game->player_data, 'P', game->map);
    character_init(game->enemy_data, 'E', game->map);
}