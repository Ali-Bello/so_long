/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 04:39:05 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 04:39:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    map_errors(t_game *game)
{
    int i;

    i = 0;
    while (game->map[i])
        free(game->map[i++]);
    free(game->map);
    if (game->error_code == 2)
        ft_putstr_fd("Error\nMAP FILE : --> [file couldn't be read]\n", 1);
    else if (game->error_code == 3)
        ft_putstr_fd("Error\nMAP FILE : --> [contains extra line break(s)]\n", 1);
    else if (game->error_code == 4)
        ft_putstr_fd("Error\nMAP FILE : --> [contains invalid character(s)]\n", 1);
    else if (game->error_code == 5)
        ft_putstr_fd("Error\nMAP FILE : --> [is not enclosed with walls]\n", 1);
    else if (game->error_code == 6)
        ft_putstr_fd("Error\nMAP FILE : --> [is not rectangular]\n", 1);
    else if (game->error_code == 7)
        ft_putstr_fd("Error\nMAP FILE : --> [contains more than 1 exit character]\n", 1);
    else if (game->error_code == 8)
        ft_putstr_fd("Error\nMAP FILE : --> [contains more than 1 player character]\n", 1);
    else if (game->error_code == 9)
        ft_putstr_fd("Error\nMAP FILE : --> [doesn't contain any collectible]\n", 1);
    else if (game->error_code == 10)
        ft_putstr_fd("Error\nMAP FILE : --> [player can't reach exit]\n", 1);
}

int error_prompts(t_game *game)
{
    if (game->error_code == 1)
        return (ft_putstr_fd("Error\n--> [malloc error]\n", 1), 1);
    else if (game->error_code > 1 && game->error_code < 11)
        return (map_errors(game), 1);
    else if (game->error_code == 11)
        return (ft_putstr_fd("Error\nMLX: --> [failed to init connection]\n", 1), 1);
    else if (game->error_code == 12)
        return (ft_putstr_fd("Error\nMLX: --> [failed to create new window]\n", 1), 1);
    else if (game->error_code == 13)
        return (ft_putstr_fd("Error\nMLX: --> [failed to create new image]\n", 1), 1);
    else if (game->error_code == 14)
        return (ft_putstr_fd("Error\nMLX: --> [failed to fetsh data from image]\n", 1), 1);
    else if (game->error_code == 15)
        return (ft_putstr_fd("Error\nMLX: --> [failed to read xpm file]\n", 1), 1);
    return (0);
}