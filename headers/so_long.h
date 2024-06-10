/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 23:42:47 by aderraj           #+#    #+#             */
/*   Updated: 2024/06/10 02:04:04 by aderraj          ###   ########.fr       */
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

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define IMG_WIDTH 64
#define IMG_HEIGHT 64

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

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_player
{
	t_animation	*current_animation;
	t_frame		*current_frame;
	int		x;
	int		y;
	int		x_px;
	int		y_px;
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
	int			player_dir;
}	t_game;

int			update_position(t_game *game);
void		update_player_xy(t_game *game);
void		move_player(t_game *game, int new_x, int new_y);
int			render_map(t_game *game);
void		render_player(t_game *game);
char		**get_map(int fd);
int			draw_map(t_game *game);
void		scale_assests(t_mlx *mlx, t_img	*imgs, int map_width, int map_height);
t_sprite	*new_sprite(char *filename, void *mlx, void *win);
void		load_animations(t_sprite *sprite, int n);
int			draw_sprite(t_sprite *sprite, int x, int y);
void		get_player_xy(t_game *game);
void 		move_player(t_game *game, int new_x, int new_y);
void		draw_animation(t_animation *animation, int x, int y);
#endif
