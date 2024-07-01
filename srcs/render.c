/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:39:30 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/01 03:51:59 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

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

void	set_asset(t_game *game, char c, int x, int y)
{
	t_sprite	*tmp;

	tmp = game->assests[0];
	if (c == '1')
		tmp = game->assests[1];
	else
		ft_cpy_img(game->assests[0]->animations->frames->img, game->bg, x, y);
	if (c == 'C')
		tmp = game->assests[2];
	else if (c == 'E')
		tmp = game->assests[3];
	if (tmp)
	{
		ft_cpy_img(tmp->animations->current_frame->img, game->bg, x, y);
		tmp->animations->current_frame = tmp->animations->current_frame->next;
		if (!tmp->animations->current_frame)
			tmp->animations->current_frame = tmp->animations->frames;
	}
}

int	render_map(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (game->map[i])
	{
		j = 0;
		x = 0;
		while (game->map[i][j])
		{
			set_asset(game, game->map[i][j], x, y);
			x += IMG_WIDTH;
			j++;
		}
		y += IMG_HEIGHT;
		i++;
	}
	return (0);
}
