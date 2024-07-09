/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:08:50 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/09 13:31:46 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void  render_collectibles(t_game *game)
{
    static int frame;
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'C')
            {
                ft_cpy_img(game->collectible[frame], game->render_img, j * TILE_SIZE, i * TILE_SIZE);
                if (frame == 3)
                    frame = 0;
                else
                    frame++;
            }
            j++;
        }
        i++;
    }
}

void    render_exit(t_game *game)
{
    static int frame;

    if (!game->collectibles_count)
    {
        ft_cpy_img(game->exit[frame], game->render_img,
            game->exit_x * TILE_SIZE,game->exit_y * TILE_SIZE);
        if (frame == 11)
            frame = 0;
        else
            frame++;
    }
    else
        ft_cpy_img(game->exit[0], game->render_img,
            game->exit_x * TILE_SIZE,game->exit_y * TILE_SIZE);
}