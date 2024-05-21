/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:18:01 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/21 00:33:54 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	draw_sprite(t_sprite *sprite, int x, int y)
{
	static t_frame	*current_frame;
	t_frame	*tmp_frame;
	int				i;

	if (sprite->animations->frame_idx == 0)
		current_frame = sprite->animations->frames;
	mlx_clear_window(sprite->mlx, sprite->win);
	mlx_put_image_to_window(sprite->mlx, sprite->win, current_frame->img->img_ptr, x, y);
	sprite->animations->delay_counter++;
	if (sprite->animations->delay_counter >= sprite->animations->frame_delay)
	{
		sprite->animations->delay_counter = 0;
		sprite->animations->frame_idx++;
		if (sprite->animations->frame_idx >= sprite->animations->frame_count)
			sprite->animations->frame_idx = 0;
		i = 0;
		tmp_frame = sprite->animations->frames;
		while (i < sprite->animations->frame_idx)
		{
			tmp_frame = tmp_frame->next;
			i++;
		}
		current_frame = tmp_frame;
	}
	return 0;
}

void	draw_map(char **map, t_sprite *sprites)
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
				draw_sprite(&sprites[1], x, y);
			else if (map[i][j] != '1')
				draw_sprite(&sprites[0], x, y);
			if (map[i][j] == 'P')
				draw_sprite(&sprites[4], x, y);
			if (map[i][j] == 'C')
				draw_sprite(&sprites[2], x, y);
			if (map[i][j] == 'E')
				draw_sprite(&sprites[3], x, y);
			j++;
			x += IMG_WIDTH;
		}
		y += IMG_HEIGHT;
		i++;
	}
}
