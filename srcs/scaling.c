/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:54:17 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/09 12:30:41 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void	my_mlx_pixel_put(t_img *img, t_scale *data, int x, int y, int color)
{
	char	*dst;

	dst = img->scaled_img + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	scale_image(t_mlx *mlx, t_img *img, t_scale *data)
{
	int		i;
	int		j;
	void	*tmp;

	img->img_data = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->line_len), &(img->endian));
	tmp = mlx_new_image(mlx->mlx, data->scaled_width, data->scaled_height);
	img->scaled_img = (char *)mlx_get_data_addr(tmp, &data->bpp,
			&data->line_len, &(img->endian));
	if (img->scaled_img == NULL)
		return ;
	i = 0;
	while (i < data->scaled_width)
	{
		j = 0;
		while (j < data->scaled_height)
		{
			data->orig_x = (int)(i / data->w_scale);
			data->orig_y = (int)(j / data->h_scale);
			data->orig_idx = data->orig_y * img->line_len + data->orig_x
				* (img->bpp / 8);
			data->scaled_idx = j * data->scaled_width * (img->bpp / 8) + i
				* (img->bpp / 8);
			my_mlx_pixel_put(img, data, i, j, *((int *)(img->img_data
						+ data->orig_idx)));
			j++;
		}
		i++;
	}
	img->img_ptr = tmp;
}

void	scale_assests(t_mlx *mlx, t_img *imgs, int map_width, int map_height)
{
	t_scale	scaling_info;
	int		i;

	scaling_info.w_scale = (SCREEN_WIDTH / (double)mlx->width);
	scaling_info.h_scale = (SCREEN_HEIGHT / (double)mlx->height);
	scaling_info.scaled_width = imgs[0].width * scaling_info.w_scale;
	scaling_info.scaled_height = imgs[0].height * scaling_info.h_scale;
	mlx->width = scaling_info.scaled_width * map_width;
	mlx->height = scaling_info.scaled_height * map_height;
	i = 0;
	while (i < 5)
		scale_image(mlx, &imgs[i++], &scaling_info);
	imgs[0].width = scaling_info.scaled_width;
	imgs[0].height = scaling_info.scaled_height;
}
