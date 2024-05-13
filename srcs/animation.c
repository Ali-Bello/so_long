/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 10:34:08 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/13 17:00:09 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

enum e_selection {
	PLAYER,
	ENEMY,
	EVENT,
	OBJ,
};

typedef struct s_animation
{
	t_list	*frames;
	int		width;
	int		height;
	int		delay;			// How many fps it takes to change animation
	int		_tmp_delay;		// Delay Iterator
	int		current_frame_num;	// Which frame is selected
	long int	last_updated;		// When was the last update
	long int	frame_count;		// The frame count
	enum e_selection	entity;
}		t_animation;

typedef struct s_sprite
{
	t_img	sprite_img;
	t_list	*animations;
	int		depth_idx;
}	t_sprite;

typedef struct s_slice
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_slice;

void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img.width && y < img.height) {
		dst = img.img_data + (y * img.line_len + x * (img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->img_data
			+ (y * img->line_len) + (x * img->bpp / 8))));
}

t_sprite	new_sprite(char *file_path, t_mlx *mlx)
{
	t_img	img;

	img.img_ptr = mlx_xpm_file_to_image(mlx, file_path, &img.width, &img.height);
	img.img_data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_len, &img.endian);
	return ((t_sprite){img, NULL, 0});
}

void	add_frame(t_animation *animation, t_sprite *sprite, t_slice *slice, t_mlx *mlx)
{
	t_img	*frame;
	int		i;
	int		j;

	frame = malloc(sizeof(t_img));
	frame->img_data = mlx_new_image(mlx, slice->width, slice->height);
	i = 0;
	while (i <= slice->width)
	{
		j = 0;
		while (j <= slice->height)
		{
			my_mlx_pixel_put(*frame, j, i, get_pixel_img(&sprite->sprite_img, slice->x + j, slice->y + i));
			j++;
		}
		i++;
	}
	ft_lstadd_back(&animation->frames, ft_lstnew(frame));
}

t_animation	*slice_sprite(t_sprite *sprite, t_slice *slice, t_mlx *mlx, int n, int delay, enum e_selection e)
{
	t_animation	*animation;
	int			i;

	animation = malloc(sizeof(t_animation));
	*animation = (t_animation){NULL, slice->width, slice->height, delay, 0, 0, 0, 0, e};
	i = 0;
	while (i < n)
	{
		add_frame(animation, sprite, slice, mlx);
		slice->x += slice->width;
		if (slice->x >= sprite->sprite_img.width)
		{
			slice->x = 0;
			slice->y += slice->height;
		}
		i++;
	}
	return (animation);
}


t_list	*ft_lstget(t_list *lst, int index)
{
	t_list	*n;
	int i;

	i = 0;
	n = lst;
	if (n == NULL)
		return (NULL);
	if (!n->next)
		return (NULL);
	while (n != NULL)
	{
		if (i >= index)
			return (n);
		n = n->next;
		i++;
	}
	return (NULL);
}

void	update_animation(void *ptr, void *mlx)
{
	t_animation	*tmp;
	t_img		*img;
	t_mlx		*m;
	int			len;

	tmp = (t_animation *)ptr;
	len = ft_lstsize(tmp->frames);
	m = (t_mlx *)mlx;
	if (!tmp)
		return ;
	if (tmp->_tmp_delay++ == tmp->delay)
	{
		tmp->_tmp_delay = 0;
		tmp->current_frame_num = ++tmp->current_frame_num % len;
		img = (t_img *)ft_lstget(tmp->frames, tmp->current_frame_num)->content;
		mlx_put_image_to_window(m->mlx, m->window, img->img_ptr, 150, 150);
	}
}
typedef struct s_tmp
{
	t_mlx *mlx;
	t_list *list;
} t_tmp;

int	update(void *data) {

	if (!((t_tmp *)(data))->list)
		return 1;
	ft_lstiter(((t_tmp *)(data))->list, ((t_tmp *)(data))->mlx, update_animation);
	return 0;
}

int main(void)
{
 	t_mlx	mlx;
	t_tmp	data;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 600, 600, "animate");
	if (!mlx.window)
		return (2);
	data.mlx = &mlx;
		/* Sprites */
		t_sprite s1 = new_sprite("textures/sprite1.xpm", &mlx);
		t_slice slice1 = (t_slice){0, 0, 160, 128};
		ft_lstadd_back(&s1.animations, ft_lstnew(slice_sprite(&s1, &slice1, &mlx, 7, 600, PLAYER)));
		printf("Sprite [%d %d], loaded %d animations\n", s1.sprite_img.width, s1.sprite_img.height, ft_lstsize(s1.animations));
		data.list = s1.animations;
		mlx_loop_hook(mlx.mlx, update, &data);
	mlx_loop(mlx.mlx);
	return (0);
}
