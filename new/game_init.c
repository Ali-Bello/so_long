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

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    int     error_code;
    t_img   *render_img;
    t_img   *wall;
    t_img   *floor;
    t_img   **player;
    t_img   **exit;
    t_img   **collectible;
    t_img   **enemy;
    t_character    *player_data;
    t_character    *enemy_data;
}   t_game;

int game_init(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        return (game->error_code = -1);
    game->map = 
}