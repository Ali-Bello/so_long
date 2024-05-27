/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:42:47 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/27 00:01:07 by aderraj          ###   ########.fr       */
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
#define IMG_WIDTH 32
#define IMG_HEIGHT 48

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

typedef struct s_player
{
	t_animation	*current_animation;
	t_frame		*current_frame;
	int		x;
	int		y;
	int		target_x;
	int		target_y;
	double		dx;
	double		dy;
	int		moving;
} t_player;

typedef struct s_sprite
{
	t_img		*img;
	t_animation	*animations;
	void		*mlx;
	void		*win;
}	t_sprite;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}	t_mlx;


typedef struct s_game
{
	t_sprite	**assests;
	t_player	*player;
	char		**map;
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



char		**get_map(int fd);
int			draw_map(t_game *game);
void		scale_assests(t_mlx *mlx, t_img	*imgs, int map_width, int map_height);
t_sprite	*new_sprite(char *filename, void *mlx, void *win);
void		load_animations(t_sprite *sprite, int n);
int			draw_sprite(t_sprite *sprite, int x, int y);
void		get_player_xy(t_game *game);
void	right_move(t_game *game);
void	left_move(t_game *game);
void	up_move(t_game *game);
void	down_move(t_game *game);
void move_player(t_game *game, int new_x, int new_y);
#endif
