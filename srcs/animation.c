#include "../headers/so_long.h"

t_sprite	*new_sprite(char *filename, void *mlx, void *win)
{
	t_sprite	*s;

	s = malloc(sizeof(t_sprite));
	if (!s)
		return (NULL);
	s->img = malloc(sizeof(t_img));
	if (!s->img)
		return (free(s), NULL);
	s->img->img_ptr = mlx_xpm_file_to_image(mlx, filename, &s->img->width, &s->img->height);
	if (!s->img->img_ptr)
		return (free(s->img), free(s), NULL);
	s->img->img_data = mlx_get_data_addr(s->img->img_ptr, &s->img->bpp, &s->img->line_len, &s->img->endian);
	s->mlx = mlx;
	s->win = win;
	s->animations = NULL;
	return (s);
}

void	ft_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->img_data
			+ (y * img->line_len) + (x * img->bpp / 8))));
}

void cpy_img(t_img *src, t_img *dst, int x, int y) {
	int	i;
	int	j;

	i = 0;
	while (i < dst->width)
	{
		j = 0;
		while (j < dst->height)
		{
			ft_mlx_pixel_put(dst, i, j, get_pixel_img(src, x + i, y + j));
			j++;
		}
			i++;
	}
}

t_img	*new_img(t_sprite	*sprite)
{
	t_img	*img;

	img = malloc (sizeof(t_img));
	if (!img)
		return (NULL);

	img->img_ptr = mlx_new_image(sprite->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!img->img_ptr)
		return (free(img), NULL);

	img->img_data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	img->width = IMG_WIDTH;
	img->height = IMG_HEIGHT;
	return (img);
}

t_frame	*new_frame(t_sprite	*sprite)
{
	t_frame	*frame;

	frame = malloc(sizeof(t_frame));
	if (!frame)
		return (NULL);

	frame->img = new_img(sprite);
	if (!frame->img)
		return (free(frame), NULL);

	cpy_img(sprite->img, frame->img, sprite->animations->x, sprite->animations->y);
	frame->next = NULL;
	return (frame);
}

void	add_animation(t_animation **head, int y, void *mlx, void *win)
{
	t_animation	*tmp;
	t_animation	*new;

	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;

	new = malloc(sizeof(t_animation));
	new->frames = NULL;
	new->current_frame = NULL;
	new->mlx = mlx;
	new->win = win;
	new->x = 0;
	new->y = y;
	new->frame_count = 6;
	new->frame_idx = 0;
	new->frame_delay = 7;
	new->delay_counter = 0;
	new->next = NULL;
	if (!tmp)
		*head = new;
	else
		tmp->next = new;
}

t_animation	*new_animations(t_sprite *sprite, int n)
{
	t_animation	*a;
	int			i;
	int			y;

	a = NULL;
	i = 0;
	y = 0;
	while (i < n && y < sprite->img->height)
	{
		add_animation(&a, y, sprite->mlx, sprite->win);
		y += IMG_HEIGHT;
		i++;
	}
	return (a);
}

void	load_frames(t_sprite *sprite, int n)
{
	t_frame	*new;
	t_frame	*tmp;
	int	i;

	i = 0;
	tmp = sprite->animations->frames;
	while (i < n && sprite->animations->x < sprite->img->width)
	{
		new = new_frame(sprite);
		if (!new)
			return ;
		if (!sprite->animations->frames)
		{
			sprite->animations->frames = new;
			tmp = sprite->animations->frames;
		}
		else
		{
			tmp->next = new;
			tmp = tmp->next;
		}
		sprite->animations->x += IMG_WIDTH;
		i++;
	}
	sprite->animations->x = 0;
}

void	load_animations(t_sprite *sprite, int n)
{
	int			i;
	t_animation	*tmp;

	if (!sprite)
		return;
	i = 0;
	sprite->animations = new_animations(sprite, n);
	if (!sprite->animations)
		return ;
	tmp = sprite->animations;
	while (i < n)
	{
		load_frames(sprite, 6);
		sprite->animations = sprite->animations->next;
		i++;
	}
	sprite->animations = tmp;
}

