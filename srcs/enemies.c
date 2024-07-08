/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:38:23 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/04 13:14:28 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

#define map_height game->height / IMG_HEIGHT
#define map_width game->width / IMG_WIDTH

void    spawn_enemy(t_game *game)
{
    char    available_positions[map_height * map_width][2];
    int     count;
    int     i;
    int     j;

    count = 0;
    i = 0;
    while (i < map_height)
    {
        j = 0;
        while (j < map_width)
        {
            if (game->map[i][j] == '0')
            {
                available_positions[count][0] = i;
                available_positions[count][1] = j;
                count++;
            }
            j++;
        }
        i++;
    }
    if (count == 0 || i == 3)
        return;
    // Seed the random number generator
    srand(time(NULL)); 
    // Select a random position from the list of zero positions
    int random_index = rand() % count;
    // Replace '0' with 'X' at the selected position
    game->map[(int)available_positions[random_index][0]]
            [(int)available_positions[random_index][1]] = 'X';
}
