/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:44:16 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 02:44:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int main(int ac, char **av)
{
    t_game  game;

    if (ac != 2)
        return (0);
    game.map = read_map(av[1], &game);
    game_allocs(&game);
    if (error_prompts(game.error_code))
        return (0);
}