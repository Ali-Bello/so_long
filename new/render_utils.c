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
                ft_cpy_img(game->floor, game->render_img, j * TILE_SIZE, i * TILE_SIZE);
                ft_cpy_img(game->collectible[frame], game->render_img, j * TILE_SIZE, i * TILE_SIZE);
            }
            j++;
        }
        i++;
    }
    if (frame == 7)
        frame = 0;
    else
        frame++;
}

void    render_exit(t_game *game)
{
    static int frame;
    static int delay;

    if (!game->collectibles_count && frame < 8)
    {
        ft_cpy_img(game->floor, game->render_img,
            game->exit_x * TILE_SIZE,game->exit_y * TILE_SIZE);
        ft_cpy_img(game->exit[frame], game->render_img,
            game->exit_x * TILE_SIZE,game->exit_y * TILE_SIZE);
        if (delay < 1)
            delay++;
        else
        {
            delay = 0;
            if (frame == 10)
                frame = 0;
            else
                frame++;
        }
    }
    else if (!game->collectibles_count && frame == 8)
        ft_cpy_img(game->exit[8], game->render_img,
            game->exit_x * TILE_SIZE,game->exit_y * TILE_SIZE);
    else
        ft_cpy_img(game->exit[0], game->render_img,
            game->exit_x * TILE_SIZE,game->exit_y * TILE_SIZE);
}