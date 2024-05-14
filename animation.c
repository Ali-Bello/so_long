/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 00:51:20 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/14 22:14:05 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/so_long.h"

#define ESC     53
#define W       13
#define A	    0
#define S	    1
#define D	    2
#define IMG_WIDTH 65
#define IMG_HEIGHT 65

typedef struct s_animation
{
	t_list	*frames;
	int		x;
	int		y;
	int		w;
	int		h;
} t_animation;

typedef struct s_sprite
{
	t_img	*img;
	t_list	*animations;
	void	*mlx;
	void	*win;
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

	// printf("sprite_img = [%p]\nimg_data = [%p]\nwidth = [%d]\nheight = [%d]\n", src->img_ptr, src->img_data, src->width, src->height);
	// printf("frame = [%p]\nimg_data = [%p]\nwidth = [%d]\nheight = [%d]\n", dst->img_ptr, dst->img_data, dst->width, dst->height);
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
	return (img);
}

int is_frame_transparent(t_img *src, int x, int y)
{
    // Ensure the image has an alpha channel (bpp should be 32 or more)
    printf("src->bpp = [%d]\n", src->bpp);
	// if (src->bpp < 32) {
    //     return 0;  // No alpha channel, assume non-transparent
    // }

    int bytes_per_pixel = src->bpp / 8;
    int alpha_offset = bytes_per_pixel - 1;  // Alpha is the last byte in each pixel (RGBA)

    for (int i = 0; i < IMG_WIDTH; i++) {
        for (int j = 0; j < IMG_HEIGHT; j++) {
            int src_index = ((y + i) * src->line_len) + ((x + j) * bytes_per_pixel);

            // Check the alpha value
            if (src->img_data[src_index + alpha_offset] != 0) {
                return 0;  // Found a non-transparent pixel
            }
        }
    }
    return 1;
}

void	load_frames(t_animation *animation, t_sprite *sprite)
{
	while (animation->x < sprite->img->width && !is_frame_transparent(sprite->img, animation->x, animation->y))
	{
		ft_lstadd_back(&animation->frames, ft_lstnew(new_frame(sprite, animation->x, animation->y)));
		animation->x += IMG_WIDTH;
	}
	animation->w = animation->x;
	animation->h = IMG_HEIGHT;
}

void	load_animations(t_sprite *sprite, int n)
{
	int	i;
	t_list	*tmp;

	i = 0;
	while (i < n)
	{
		ft_lstadd_back(&sprite->animations, ft_lstnew(malloc(sizeof(t_animation))));
		i++;
	}
	(*((t_animation *)(sprite->animations->content))) = (t_animation){NULL, 0, 0, 0, 0};
	tmp = sprite->animations;
	while (tmp && tmp->next)
	{
		((t_animation *)(tmp->next->content))->x = 0;
		((t_animation *)(tmp->next->content))->y = ((t_animation *)(tmp->content))->y + IMG_HEIGHT;
		load_frames(tmp->content, sprite);
		tmp = tmp->next;
	}
}

void	draw_assets(t_mlx *mlx, t_sprite *sprite)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = sprite->animations;
	while (tmp)
	{
		tmp2 = ((t_animation *)(tmp->content))->frames;
		while (tmp2)
		{
			mlx_put_image_to_window(mlx->mlx, mlx->window, ((t_img *)(tmp2))->img_ptr, 150, 150);
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
	mlx.window = mlx_new_window(mlx.mlx, 1920, 1080, "ANIMATION TEST");
	sprite = new_sprite("textures/Player.xpm", mlx.mlx, mlx.window);
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
