/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:42:47 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/13 13:48:49 by aderraj          ###   ########.fr       */
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

char	**get_map(int fd);
void	draw_map(char **map, t_img *img, t_mlx *mlx);
int		move_right(char **map, t_game *game);
int		move_left(char **map, t_game *game);
int		move_up(char **map, t_game *game);
int		move_down(char **map, t_game *game);
void	scale_assests(t_mlx *mlx, t_img	*imgs, int map_width, int map_height);
#endif
