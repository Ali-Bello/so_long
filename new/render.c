/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:28:42 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/09 16:38:31 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int get_animation_idx(int direction)
{
    if (direction == 0)
        return (0);
    if (direction == 1)
        return (6);
    if (direction == 2)
        return (12);
    if (direction == 3)
        return (18);
    if (direction == 4)
        return (24);
    return (0);
}

void	ft_cpy_pixel(t_img *src, t_img *dst, int src_idx, int dst_idx)
{
	int	i;

	i = 0;
	while (i < src->bpp / 8)
	{
		if (src->img_data[src_idx + i])
			dst->img_data[dst_idx + i] = src->img_data[src_idx + i];
		i++;
	}
}

void	ft_cpy_img(t_img *src, t_img *dst, int x, int y)
{
	int	i;
	int	j;
	int	src_idx;
	int	dst_idx;

	i = 0;
	while (i < src->height && (y + i) < dst->height)
	{
		j = 0;
		while (j < src->width && (x + j) < dst->width)
		{
			src_idx = (i * src->line_len) + (j * src->bpp / 8);
			dst_idx = ((y + i) * dst->line_len) + ((x + j) * src->bpp / 8);
			ft_cpy_pixel(src, dst, src_idx, dst_idx);
			j++;
		}
		i++;
	}
}

void    render_map(t_game *game)
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
                ft_cpy_img(game->wall, game->render_img, j * TILE_SIZE, i * TILE_SIZE);
            else
                ft_cpy_img(game->floor, game->render_img, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
}

int render_game(t_game *game)
{
    render_collectibles(game);
    render_exit(game);
    render_player(game);
    render_enemy(game);
    mlx_put_image_to_window(game->mlx, game->win,
            game->render_img->img_ptr, 0, 0);
    if (!game->collectibles_count && game->player_data->x == game->exit_x
            && game->player_data->y == game->exit_y)
    {
        mlx_string_put(game->mlx, game->win, 10, 10, 0x00FFFFFF, "You won!");
        error_prompts(game);
        exit(0);
    }
    if (game->player_data->x == game->enemy_data->x
            && game->player_data->y == game->enemy_data->y)
    {
        mlx_string_put(game->mlx, game->win, 10, 10, 0x00FFFFFF, "You lost!");  
        error_prompts(game);
        exit(0);
    }
    usleep(16670);
	return (0);
}
