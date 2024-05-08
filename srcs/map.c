/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:18:01 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/08 10:41:19 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	draw_map(char **map, t_img *imgs, t_mlx *mlx)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	y = 0;
	while (map[i])
	{
		j = 0;
		x = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(mlx->mlx, mlx->window, imgs[0].img_ptr, x, y);
			else if (map[i][j] != '1')
				mlx_put_image_to_window(mlx->mlx, mlx->window, imgs[1].img_ptr, x, y);
			if (map[i][j] == 'P')
				mlx_put_image_to_window(mlx->mlx, mlx->window, imgs[2].img_ptr, x, y);
			if (map[i][j] == 'C')
				mlx_put_image_to_window(mlx->mlx, mlx->window, imgs[3].img_ptr, x, y);
			if (map[i][j] == 'E')
				mlx_put_image_to_window(mlx->mlx, mlx->window, imgs[4].img_ptr, x, y);
			j++;
			x += imgs[0].width * imgs[0].scale;
		}
		y += imgs[0].height * imgs[0].scale;
		i++;
	}
}
