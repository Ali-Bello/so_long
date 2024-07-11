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

#include "../headers/so_long.h"

t_img    **alloc_animation(int n, int *error_code)
{
    int i;
    t_img **ptr;

    ptr = malloc(sizeof(t_img *) * n);
    if (!ptr)
    {
        *error_code = 1;
        return (NULL);
    }
    i = 0;
    while (i < n - 1)
    {
        ptr[i] = malloc(sizeof(t_img));
        if (!ptr[i])
        {
            *error_code = 1;
            return (ptr);
        }
        ptr[i]->img_ptr = NULL;
        ptr[i]->img_data = NULL;
        i++;
    }
    ptr[i] = NULL;
    return (ptr);
}

int load_frames(t_game *game, t_img **ptr, int n, char *path)
{
    int     i;
    char    *frame_path;
    char    *tmp;

    i = 0;
    while (i < n - 1)
    {
        tmp = ft_strjoin(ft_itoa(i), ".xpm");
        frame_path = ft_strjoin(ft_strdup(path), tmp);
        free(tmp);
        if (!frame_path)
            return (game->error_code = 1);
        ptr[i]->img_ptr = mlx_xpm_file_to_image(game->mlx, frame_path, &ptr[i]->width, &ptr[i]->height);
        free(frame_path);
        if (!ptr[i]->img_ptr)
            return (game->error_code = 15);
        ptr[i]->img_data = mlx_get_data_addr(ptr[i]->img_ptr, &ptr[i]->bpp, &ptr[i]->line_len, &ptr[i]->endian);
        if (!ptr[i]->img_data)
            return (game->error_code = 14);
        i++;
    }
    return (0);
}

int load_assets(t_game *game)
{
    game->render_img->img_ptr = mlx_new_image(game->mlx, game->map_width * TILE_SIZE,
                                game->map_height * TILE_SIZE);
    if (!game->render_img->img_ptr)
        return (game->error_code = 13);
    game->render_img->width = game->map_width * TILE_SIZE;
    game->render_img->height = game->map_height * TILE_SIZE;
    game->render_img->img_data = mlx_get_data_addr(game->render_img->img_ptr,
        &game->render_img->bpp, &game->render_img->line_len, &game->render_img->endian);
    if (!game->render_img->img_data)
        return (game->error_code = 14);
    game->wall->img_ptr = mlx_xpm_file_to_image(game->mlx, "assets/Wall/Wall.xpm", &game->wall->width, &game->wall->height);
    if (!game->wall->img_ptr)
        return (game->error_code = 15);
    game->wall->img_data = mlx_get_data_addr(game->wall->img_ptr, &game->wall->bpp, &game->wall->line_len, &game->wall->endian);
    if (!game->wall->img_data)
        return (game->error_code = 14);
    game->floor->img_ptr = mlx_xpm_file_to_image(game->mlx, "assets/Floor/Grass.xpm", &game->floor->width, &game->floor->height);
    if (!game->floor->img_ptr)
        return (game->error_code = 15);
    game->floor->img_data = mlx_get_data_addr(game->floor->img_ptr, &game->floor->bpp, &game->floor->line_len, &game->floor->endian);
    if (!game->floor->img_data)
        return (game->error_code = 14);
    load_frames(game, game->player, 31, "assets/Player/");
    load_frames(game, game->enemy, 21, "assets/enemy/");
    load_frames(game, game->collectible, 9, "assets/Collectible/");
    load_frames(game, game->exit, 12, "assets/Exit/");
    return (0);
}

t_img   *alloc_image(int *error_code)
{
    t_img *img; 

    img = malloc(sizeof(t_img));
    if (!img)
    {
        *error_code = 1;
        return (NULL);
    }
    img->img_ptr = NULL;
    img->img_data = NULL;
    return (img);

}
int game_allocs(t_game *game)
{
    game->render_img = alloc_image(&game->error_code);
    game->wall = alloc_image(&game->error_code);
    game->floor = alloc_image(&game->error_code);
    if (game->error_code)
        return (game->error_code);
    game->player = alloc_animation(31, &game->error_code);
    game->enemy = alloc_animation(21, &game->error_code);
    game->exit = alloc_animation(12, &game->error_code);
    game->collectible = alloc_animation(9, &game->error_code);
    if (game->error_code)
        return (game->error_code);
    game->player_data = malloc(sizeof(t_character));
    if (!game->player_data)
        return (game->error_code = 1);
    game->enemy_data = malloc(sizeof(t_character));
    
    return (0);
}