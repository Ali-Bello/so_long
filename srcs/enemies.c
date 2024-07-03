/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:38:23 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/03 01:10:24 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

#define map_height game->height / IMG_HEIGHT
#define map_width game->width / IMG_WIDTH

void    spawn_enemies(t_game *game)
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
}