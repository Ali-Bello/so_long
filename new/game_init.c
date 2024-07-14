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

#include "../headers/so_long.h"

int get_collectibles_count(char **map)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'C')
                count++;
            j++;
        }
        i++;
    }
    return (count);
}

void    character_init(t_character *character, char c, char **map)
{
    get_position(c, map, &character->y, &character->x);
    character->prev_x = character->x;
    character->prev_y = character->y;
    character->x *= TILE_SIZE;
    character->y *= TILE_SIZE;
    character->target_x = character->x;
    character->target_y = character->y;
    character->direction = 0;
    character->animation_frame = 0;
    character->animation_idx = 0;
    character->step = 0;
}

void    game_init(t_game *game, char *path)
{
    ft_memset(game, 0, sizeof(t_game));
    game_allocs(game);
    game->map = read_map(path, game);
    if (game->error_code)
        return ;
    game->map_width = ft_strlen(game->map[0]);
    game->map_height = get_height(game->map);
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        game->error_code = 11;
        return ;
    }
    load_assets(game);
    if (game->error_code)
        return ;
    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, 
                                game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
    {
        game->error_code = 12;
        return ;
    }
    game->collectibles_count = get_collectibles_count(game->map);
    spawn_enemy(game);
    character_init(game->player_data, 'P', game->map);
    character_init(game->enemy_data, 'X', game->map);
    get_position('E', game->map, &game->exit_y, &game->exit_x);
}