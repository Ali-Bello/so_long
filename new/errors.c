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

#include "../headers/so_long.h"

void    free_map(char **map)
{
    int i;

    i = 0;
    if (!map)
        return ;
    while (map[i])
        free(map[i++]);
    free(map);
    map = NULL;
}

void    free_image(t_img *img, void *mlx)
{
    if (img->img_ptr)
        mlx_destroy_image(mlx, img->img_ptr);
    // if (img->img_data)
    //     free(img->img_data);
    free(img);
}

void    free_sprite(t_img **sprite, void *mlx)
{
    int i;

    i = 0;
    if (!sprite)
        return ;
    while (sprite[i])
    {
        free_image(sprite[i], mlx);
        i++;
    }
    free(sprite);
}

void    free_memory(t_game *game)
{
    free_map(game->map);
    free_image(game->render_img, game->mlx);
    free_image(game->wall, game->mlx);
    free_image(game->floor, game->mlx);
    free_sprite(game->player, game->mlx);
    free_sprite(game->exit, game->mlx);
    free_sprite(game->collectible, game->mlx);
    free_sprite(game->enemy, game->mlx);
    if (game->player_data)
        free(game->player_data);
    if (game->enemy_data)
        free(game->enemy_data);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}

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
        ft_putstr_fd("Error\n--> [malloc error]\n", 1);
    else if (game->error_code > 1 && game->error_code < 11)
        map_errors(game);
    else if (game->error_code == 11)
        ft_putstr_fd("Error\nMLX: --> [failed to init connection]\n", 1);
    else if (game->error_code == 12)
        ft_putstr_fd("Error\nMLX: --> [failed to create new window]\n", 1);
    else if (game->error_code == 13)
        ft_putstr_fd("Error\nMLX: --> [failed to create new image]\n", 1);
    else if (game->error_code == 14)
        ft_putstr_fd("Error\nMLX: --> [failed to fetsh data from image]\n", 1);
    else if (game->error_code == 15)
        ft_putstr_fd("Error\nMLX: --> [failed to read xpm file]\n", 1);
    free_memory(game);
    exit(0);
    return (0);
}
