/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:42:47 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/21 00:34:06 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include <mlx.h>
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define IMG_WIDTH 65
#define IMG_HEIGHT 65

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_data;
	char	*scaled_img;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_scale
{
	int		orig_x;
	int		orig_y;
	int		orig_idx;
	int		scaled_width;
	int		scaled_height;
	int		bpp;
	int		line_len;
	int		scaled_idx;
	double	w_scale;
	double	h_scale;
}	t_scale;

typedef struct s_game
{
	int	collectibles;
	int	collected;
	int	moves;
}	t_game;

typedef struct s_data
{
	t_game	*game;
	char	**map;
	t_img	*img;
	t_mlx	*mlx;
} t_data;

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
	int					frame_idx;
	int					frame_count;
	int					frame_delay;
	int					delay_counter;
	struct s_animation	*next;
} t_animation;

typedef struct s_sprite
{
	t_img		*img;
	t_animation	*animations;
	void		*mlx;
	void		*win;
}	t_sprite;

char	**get_map(int fd);
void	draw_map(char **map, t_sprite *img);
int		move_right(char **map, t_game *game);
int		move_left(char **map, t_game *game);
int		move_up(char **map, t_game *game);
int		move_down(char **map, t_game *game);
void	scale_assests(t_mlx *mlx, t_img	*imgs, int map_width, int map_height);
t_sprite	*new_sprite(char *filename, void *mlx, void *win);
void	load_animations(t_sprite *sprite, int n);
#endif
