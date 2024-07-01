/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:42:47 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/01 04:19:47 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include "mlx.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define IMG_WIDTH 64
#define IMG_HEIGHT 64
#define STEP_SIZE 4

typedef struct s_img
{
	void	*img_ptr;
	char	*img_data;
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
	t_frame				*current_frame;
	void				*mlx;
	void				*win;
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


typedef struct s_player
{
	t_animation	*current_animation;
	t_frame		*current_frame;
	int		x;
	int		y;
	int		x_px;
	int		y_px;
	int		init_x;
	int		init_y;
	int		target_x;
	int		target_y;
	int		is_moving;
} t_player;

typedef struct s_game
{
	t_sprite	**assests;
	t_img		*bg;
	t_player	*player;
	char		**map;
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	int			collectibles;
	int			collected;
	int			moves;
	int			move_delay;
	int			player_dir;
}	t_game;

void		ft_cpy_pixel(t_img *src, t_img *dst, int src_idx, int dst_idx);
void		ft_cpy_img(t_img *src, t_img *dst, int x, int y);
int			update_player(t_game *game);
void 		move_player(t_game *game, int new_x, int new_y);
void 		set_positions(t_game *game, int new_x, int new_y);
int 		render_map(t_game *game);
void 		render_player(t_game *game);
char 		**get_map(int fd);
t_sprite 	*new_sprite(char *filename, void *mlx, void *win);
void		load_animations(t_sprite *sprite, int n);
void		get_player_mapxy(t_game *game);

#endif
