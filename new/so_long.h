/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:25:16 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 03:25:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include "mlx.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TILE_SIZE 64

typedef struct s_img
{
    void    *img_ptr;
    char    *img_data;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_character
{
    int x;
    int y;
    int target_x;
    int target_y;
    int direction;
}   t_character;


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

int game_allocs(t_game *game);
int error_prompts(t_game *game);
int load_assets(t_game *game);
void    game_init(t_game *game, char *path);
void    spawn_enemy(t_game *game);

/**PARSING**/
int read_map(char *path, t_game *game);
int	get_height(char **map);
char	**duplicate_map(char **map);
void	get_position(char c, char **map, int *y, int *x);
void    flood_fill(char **map, int x, int y);
/**********/

/**RENDER**/
void    render_map(t_game *game);
/*********/
#endif