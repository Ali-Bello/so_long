/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:26:40 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 03:26:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int alloc_frames(t_img **ptr, int n, int *error_code)
{
    int i;

    i = 0;
    while (i < n - 1)
    {
        ptr[i] = malloc(sizeof(t_img));
        if (!ptr[i])
            return (*error_code = 1);
        i++;
    }
    ptr[i] = NULL;
    return (0);
}

void    alloc_animation(t_img **ptr, int n, int *error_code)
{
    ptr = malloc(sizeof(t_img *) * n);
    if (!ptr)
        *error_code = 1;
    alloc_frames(ptr, n, error_code);
}

int game_allocs(t_game *game)
{
    game->render_img = malloc(sizeof(t_img));
    if (!game->render_img)
        return (game->error_code = 1);
    game->wall = malloc(sizeof(t_img));
    if (!game->wall)
        return (game->error_code = 1);
    game->floor = malloc(sizeof(t_img));
    if (!game->floor)
        return (game->error_code = 1);
    alloc_animation(game->player, 31, &game->error_code);
    alloc_animation(game->enemy, 21, &game->error_code);
    alloc_animation(game->exit, 12, &game->error_code);
    alloc_animation(game->collectible, 5, &game->error_code);
    game->player_data = malloc(sizeof(t_character));
    if (!game->player_data)
        return (game->error_code = 1);
    game->enemy_data = malloc(sizeof(t_character));
    return (0);
}