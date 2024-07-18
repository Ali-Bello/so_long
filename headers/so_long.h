/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:25:16 by marvin            #+#    #+#             */
/*   Updated: 2024/07/17 18:24:52 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include "libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define TILE_SIZE 64
# define STEP_SIZE 8

typedef struct s_img
{
	void		*img_ptr;
	char		*img_data;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_character
{
	int			x;
	int			y;
	int			target_x;
	int			target_y;
	int			direction;
	int			animation_frame;
	int			animation_idx;
	int			step;
}				t_character;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_width;
	int			map_height;
	int			error_code;
	int			moves_count;
	int			collectibles_count;
	int			exit_x;
	int			exit_y;
	int			enemy_flag;
	t_img		*render_img;
	t_img		*wall;
	t_img		*floor;
	t_img		**player;
	t_img		**exit;
	t_img		**collectible;
	t_img		**enemy;
	t_character	*player_data;
	t_character	*enemy_data;
}				t_game;

int				game_allocs(t_game *game);
int				error_prompts(t_game *game);
int				load_assets(t_game *game);
void			spawn_enemy(t_game *game);
void			game_init(t_game *game, char *path);
void			set_available_space(t_game *game, char arr[][2], int *count);
int				move_player(t_game *game, int new_x, int new_y);
void			update_character(t_character *character, int step);
void			free_map(char **map);
int				load_image(t_img *img, char *path, void *mlx, int *error_code);

/**PARSING**/
char			**read_map(char *path, t_game *game);
char			**duplicate_map(char **map);
int				get_height(char **map);
int				is_border(char *str);
int				is_rectangular(char **map);
int				is_unique(char **map, char c);
int				is_valid_chars(char **map, char *charset);
int				has_collectible(char **map);
int				path_check(char **map);
void			get_position(char c, char **map, int *y, int *x);
void			flood_fill(char **map, int x, int y);
int				open_file(char *name, int *error_code);
/**********/

/**RENDER**/
void			ft_cpy_img(t_img *src, t_img *dst, int x, int y);
void			render_map(t_game *game);
void			render_wall(t_game *game, int i, int j);
void			render_player(t_game *game);
void			render_enemy(t_game *game);
void			render_exit(t_game *game);
void			render_counter(t_game *game);
int				render_game(t_game *game);
void			render_free_space(t_game *game);
int				get_animation_idx(int direction, int frames);
/*********/
#endif