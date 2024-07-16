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

void    render_free_space(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '0')
                ft_cpy_img(game->floor, game->render_img, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
}

void    render_walls(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
            {
                ft_cpy_img(game->floor, game->render_img, j * TILE_SIZE, i * TILE_SIZE);
                if (i > 0 && i <= game->map_height - 1 && game->map[i - 1][j] == '1')
                {
                    ft_cpy_img(game->wall, game->render_img, j * TILE_SIZE, (i * TILE_SIZE) - 42);
                    ft_cpy_img(game->wall, game->render_img, j * TILE_SIZE, (i * TILE_SIZE) - 21);
                }
                if (j > 0 && j <= game->map_width - 1 && game->map[i][j - 1] == '1')
                    ft_cpy_img(game->wall, game->render_img, (j * TILE_SIZE) - 32, i * TILE_SIZE);
                ft_cpy_img(game->wall, game->render_img, j * TILE_SIZE, i * TILE_SIZE);
            }
            j++;
        }
        i++;
    }

}

void    render_exit(t_game *game)
{
    static int frame;
    static int delay;

    if (!game->collectibles_count && frame < 8)
    {
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

void    render_counter(t_game *game)
{
    char    *str;

    str = ft_itoa(game->moves_count);
    mlx_string_put(game->mlx, game->win, 10, 10, 0x00FFFFFF, str);
    free(str);
}