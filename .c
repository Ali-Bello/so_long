#include "headers/so_long.h"

#define ESC     53
#define W       13
#define A	    0
#define S	    1
#define D	    2
#define IMG_WIDTH 160
#define IMG_HEIGHT 128
#define RIGHT_MOVE_FRAMES_NUM 5

typedef struct s_frame
{
	t_img	*img;
	struct s_frame	*next;
} t_frame;

typedef struct s_animation
{
	t_frame				*frames;
	int					x;
	int					y;
	int					w;
	int					h;
	struct s_animation	*next;
} t_animation;

typedef struct s_sprite
{
	t_img		*img;
	t_animation	*animations;
	void		*mlx;
	void		*win;
}	t_sprite;

void	cpy_pixel(t_img *src, t_img *dst, int src_idx, int dst_idx)
{
	int	i;

	i = 0;
	while (i < src->bpp / 8)
	{
		dst->img_data[dst_idx + i] = src->img_data[src_idx + i];
		i++;
	}
}

void	cpy_img(t_img *src, t_img *dst, int x, int y)
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
			dst_idx = ((y + i) * dst->line_len) + ((x + j) * src->bpp /8);
			cpy_pixel(src, dst, src_idx, dst_idx);
			j++;
		}
		i++;
	}
}

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
	s->img->img_data = mlx_get_data_addr(s->img->img_ptr, &s->img->bpp, &s->img->line_len, &s->img->endian);
	s->mlx = mlx;
	s->win = win;
	s->animations = NULL;
	return (s);
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

t_frame	*new_frame(t_sprite	*sprite, int x, int y)
{
	t_frame	*frame;

	frame = malloc(sizeof(t_frame));
	if (!frame)
		return (NULL);

	frame->img = new_img(sprite);
	if (!frame->img)
		return (free(frame), NULL);

	cpy_img(sprite->img, frame->img, x, y);
	frame->next = NULL;
	return (frame);
}

t_animation	*new_animations(int n)
{
	t_animation	*a;
	t_animation	*tmp;
	int			i;

	a = NULL;
	i = 0;
	tmp = a;
	while (i < n)
	{
		tmp = malloc(sizeof(t_animation));
		if (!tmp)
			return (NULL);
		*tmp = (t_animation){NULL, 0, 0, 0, 0, NULL};
		tmp = tmp->next;
		i++;
	}
	tmp = NULL;
	tmp = a;
	while (tmp && tmp->next)
	{
		tmp->next->y = tmp->y + IMG_HEIGHT;
		tmp = tmp->next;
	}
	return (a);
}

void	load_frames(t_sprite *sprite, int n)
{
	t_frame	*tmp;
	int	i;

	i = 0;
	tmp = sprite->animations->frames;
	while (i < n)
	{
		tmp = new_frame(sprite, sprite->animations->x, sprite->animations->y);
		if (!tmp)
			return ;
		sprite->animations->x += IMG_WIDTH;
		tmp = tmp->next;
		i++;
	}
	sprite->animations->x = 0;
}

void	load_animations(t_sprite *sprite, int n)
{
	int	i;

	i = 0;
	sprite->animations = new_animations(n);
	if (!sprite->animations)
		return ;
	while (i < n)
	{
		load_frames(sprite, 5);
		i++;
	}
}

void	draw_assets(t_sprite *sprite)
{
	t_animation	*tmp;
	t_frame		*tmp2;

	tmp = sprite->animations;
	while (tmp)
	{
		tmp2 = tmp->frames;
		while (tmp2)
		{
			mlx_put_image_to_window(sprite->mlx, sprite->win, tmp2->img->img_ptr, 150, 150);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}
int main()
{
	t_mlx	mlx;
	t_sprite	*sprite;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 1980, 1080, "nuh");
	sprite = new_sprite("textures/Player.xpm", mlx.mlx, mlx.window);

	load_animations(sprite, 7);
	draw_assets(sprite);
	mlx_loop(mlx.mlx);
}
