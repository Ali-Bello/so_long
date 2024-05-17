/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 00:51:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/16 00:33:00 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/so_long.h"

#define ESC     53
#define W       13
#define A	    0
#define S	    1
#define D	    2
#define IMG_WIDTH 160
#define IMG_HEIGHT 128

typedef struct s_frame
{
	t_img	*img;
	struct s_frame	*next;
} t_frame;

typedef struct s_animation
{
	t_frame				*frames;
	int					n_frames;
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

t_sprite	*new_sprite(char *filename, void *mlx, void *window)
{
	t_sprite	*s;

	s = malloc (sizeof(t_sprite));
	if (!s)
		return ((t_sprite *)NULL);
	s->img = malloc(sizeof(t_img));
	if (!s->img)
		return ((t_sprite *)(NULL));
	s->img->img_ptr = mlx_xpm_file_to_image(mlx, filename, &s->img->width, &s->img->height);
	s->img->img_data = mlx_get_data_addr(s->img->img_ptr, &s->img->bpp, &s->img->line_len, &s->img->endian);
	s->mlx = mlx;
	s->win = window;
	s->animations = NULL;
	return (s);
}

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

t_img	*new_frame(t_sprite	*sprite, int x, int y)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return ((t_img *)NULL);
	img->img_ptr = mlx_new_image(sprite->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!img->img_ptr)
		return ((t_img *)NULL);
	img->img_data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
	img->width = IMG_WIDTH;
	img->height = IMG_HEIGHT;
	cpy_img(sprite->img, img, x, y);
	// mlx_put_image_to_window(sprite->mlx, sprite->win, img->img_ptr, 150, 150);
	return (img);
}

void	load_frames(t_animation *animation, t_sprite *sprite)
{
	t_frame	*tmp;
	t_frame	*new;

	if (!animation->frames)
	{
		animation->frames = malloc(sizeof(t_frame));
		animation->frames->img = NULL;
		animation->frames->next = NULL;
	}
	tmp = animation->frames;
	while (animation->x < (IMG_WIDTH * 4))
	{
		tmp->img = new_frame(sprite, animation->x, animation->y);
		new = malloc(sizeof(t_frame));
		if (!new)
			return;
		new->next = NULL;
		tmp->next = new;
		tmp = tmp->next;
		animation->x += IMG_WIDTH;
	}
	tmp = animation->frames;
	printf("\n-------\n");
	while (tmp)
	{
		printf("animation->frames = [%p]\n", tmp);
		printf("frames->img->img_ptr = [%p]\n", tmp->img->img_ptr);
		tmp = tmp->next;
	}
	animation->w = animation->x;
	animation->h = IMG_HEIGHT;
}

t_animation	*new_animation()
{
	t_animation	*ptr;

	ptr = malloc(sizeof(t_animation));
	if (!ptr)
		return (NULL);
	ptr->frames = NULL;
	ptr->next = NULL;
	ptr->x = 0;
	ptr->y = 0;
	return (ptr);
}
void	load_animations(t_sprite *sprite, int n)
{
	int	i;
	t_animation	*tmp;

	i = 0;
	sprite->animations = new_animation();
	tmp = sprite->animations;
	while (i < n - 1)
	{
		tmp->next = new_animation();
		tmp = tmp->next;
		i++;
	}
	tmp = sprite->animations;
	while (tmp)
	{
		printf("!!! -> sprite->animations = [%p]\n", tmp);
		if (tmp->next)
			tmp->next->y = tmp->y + IMG_HEIGHT;
		load_frames(tmp, sprite);
		tmp = tmp->next;
	}

}

void	draw_assets(t_mlx *mlx, t_sprite *sprite)
{
	t_animation *tmp;
	t_frame		*tmp2;

	// tmp = sprite->animations;
	// while (tmp)
	// {
	// 	printf("\n-------------\n");
	// 	printf("sprite->animations = [%p]\n", sprite->animations);
	// 	tmp2 = sprite->animations->frames;
	// 	while (tmp2)
	// 	{
	// 		printf("frame->img_ptr = [%p]\ntmp2->img_data =[%p]\ntmp2->img_width = [%d]\ntmp2->img_height = [%d]\n", tmp2->img->img_ptr, tmp2->img->img_data, tmp2->img->width, tmp2->img->height);
	// 		tmp2 = tmp2->next;
	// 	}
	// 	printf("\n-------------\n");
	// 	tmp = tmp->next;
	// }
	tmp = sprite->animations;
	while (tmp)
	{
		tmp2 = tmp->frames;
		while (tmp2)
		{
			mlx_put_image_to_window(mlx->mlx, mlx->window, tmp2->img->img_ptr, 150, 150);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int main()
{
	t_sprite	*sprite;
	t_mlx		mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, 900, 900, "ANIMATION TEST");
	sprite = new_sprite("textures/Player.xpm", mlx.mlx, mlx.window);
	printf("sprite [%p]\n", sprite);
	printf("sprite->img_ptr = [%p]\nsprite->img_data =[%p]\nsprite->img_width = [%d]\nsprite->img_height = [%d]\n", sprite->img->img_ptr, sprite->img->img_data, sprite->img->width, sprite->img->height);
	printf("sprite->img_bpp = [%d]\nsprite->img_line_len = [%d]\nsprite->img_endian = [%d]\n", sprite->img->bpp, sprite->img->line_len, sprite->img->endian);
	printf("sprite->animations = [%p]\n", sprite->animations);
	load_animations(sprite, 5);
	draw_assets(&mlx, sprite);
	mlx_loop(mlx.mlx);
}
// int keys(int keycode, t_vars *vars)
// {
//     if (keycode == ESC)
//     {
//             mlx_destroy_window(vars->mlx, vars->win);
//             free(vars);
//             exit(-1);
//         }
//         if (keycode == W)
//             vars->box_y -= 10;
//         if (keycode == A)
//             vars->box_x -= 10;
//         if (keycode == S)
//             vars->box_y += 10;
//         if (keycode == D)
//             vars->box_x += 10;
//     return (0);
// }

// int render_car(t_vars *vars)
// {
//     int x;
//     int y;

//     x = 350;
//     y = 350;
//     mlx_clear_window(vars->mlx, vars->win);
//     while(x < 450)
//     {
//         while(y < 450)
//         {
//          mlx_put_image_to_window(vars->mlx, vars->win, vars->car->img, vars->car->x, vars->car->y);
//         }
//         y++;
//         }
//     y = 350;
//     x++;
//     }
//     mlx_do_sync(vars->mlx);
//     return(1);
// }

// int main()
// {
//     t_vars  *vars;

//     vars = NULL;
//     vars = malloc(sizeof(t_vars));

//     vars->car = malloc(sizeof(t_obj));
//     vars->car->x = 0;
//     vars->car->y = 0;
//     vars->car->next = NULL;
//     vars->car->img = mlx_xpm_file_to_image(vars->mlx, "./texture.xpm", &vars->car->w, &vars->car->h);


//     vars->mlx = mlx_init();
//     vars->win = mlx_new_window(vars->mlx, 1920 , 1080 , "HELLO");

//     mlx_loop_hook(vars->mlx, render_car, vars);
//     mlx_hook(vars->win, 2, 0, keys, vars);
//     mlx_loop(vars->mlx);
// }
