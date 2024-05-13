/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:03:11 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/13 23:35:28 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

typedef struct s_sprite
{
	t_list	*animations;
	t_img	*img;
} t_sprite;

typedef struct s_slice
{
	int	x;
	int	y;
	int	w;
	int	h;
} t_slice;

typedef struct s_animation
{
	t_list	*frames;
} t_animation;

t_sprite	*new_sprite(char *file_path, t_mlx *mlx)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	sprite->img->img_ptr = mlx_xpm_file_to_image(mlx->mlx, file_path, &sprite->img->width, &sprite->img->height);
	sprite->img->img_data = mlx_get_data_addr(sprite->img->img_ptr, &sprite->img->bpp, &sprite->img->line_len, &sprite->img->endian);
	return (sprite);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img->width && y < img->height) {
		dst = img->img_data + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->img_data
			+ (y * img->line_len) + (x * img->bpp / 8))));
}

void	add_frame(t_animation *animation, t_img *sprite_img, t_slice *slice, t_mlx *mlx)
{
	t_img	*frame;
	int		i;
	int		j;

	frame = malloc(sizeof(t_img));
	frame->img_ptr = mlx_new_image(mlx->mlx, 65, 65);
	frame->img_data = mlx_get_data_addr(frame->img_ptr, &frame->bpp, &frame->line_len, &frame->endian);

	i = 0;
	while (i < 65)
	{
		j = 0;
		while (j < 65)
		{
			my_mlx_pixel_put(frame, j, i, get_pixel_img(sprite_img, slice->x + j, slice->y + i));
			j++;
		}
		i++;
	}
	ft_lstadd_back(&animation->frames, ft_lstnew(frame));
}

t_animation	*add_slice_frames(t_sprite *sprite, t_slice *slice, t_mlx *mlx)
{
	t_animation	*animation;
	int			i;

	animation = malloc (sizeof (t_animation));
	i = 0;
	while (slice->x < slice->w)
	{
		add_frame(animation, sprite->img, slice, mlx);
		slice->x += 65;
	}
	return (animation);
}
