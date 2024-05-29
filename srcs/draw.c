/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:18:01 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/29 01:24:05 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void draw_animation(t_animation *animation, int x, int y, void *mlx, void *win)
{
	static t_frame *current_frame = NULL;

	(void)mlx;
	(void)win;
	if (!animation || !animation->frames)
		return;
	if (animation->frame_idx == 0)
		current_frame = animation->frames;
	if (current_frame && current_frame->img)
		mlx_put_image_to_window(mlx, win, current_frame->img->img_ptr, x, y);
	animation->delay_counter++;
	if (animation->delay_counter >= animation->frame_delay)
	{
		animation->delay_counter = 0;
		animation->frame_idx++;
		if (animation->frame_idx >= animation->frame_count)
			animation->frame_idx = 0;
		current_frame = animation->frames;
		for (int i = 0; i < animation->frame_idx; i++) {
			if (current_frame->next)
			current_frame = current_frame->next;
		}
	}
}


int	draw_sprite(t_sprite *sprite, int x, int y)
{
	static t_frame	*current_frame;
	t_frame	*tmp_frame;
	int				i;

	if (!sprite || !sprite->animations )
		return (0);
	if (sprite->animations->frame_idx == 0)
		current_frame = sprite->animations->frames;
	mlx_put_image_to_window(sprite->mlx, sprite->win, current_frame->img->img_ptr, x, y);
	sprite->animations->delay_counter++;
	if (sprite->animations->delay_counter >= sprite->animations->frame_delay)
	{
		sprite->animations->delay_counter = 0;
		sprite->animations->frame_idx++;
		if (sprite->animations->frame_idx >= sprite->animations->frame_count)
			sprite->animations->frame_idx = 0;
		i = 0;
		tmp_frame = sprite->animations->frames;
		while (i < sprite->animations->frame_idx)
		{
			tmp_frame = tmp_frame->next;
			i++;
		}
		current_frame = tmp_frame;
	}
	return 0;
}

void	draw_player(t_game *game)
{
	static int	x;

	if (!x)
		x = 5;
	mlx_put_image_to_window(game->assests[0]->mlx, game->assests[0]->win,
		game->assests[0]->img->img_ptr, game->player->x * IMG_WIDTH,
		game->player->y * IMG_HEIGHT);
	if (game->player_dir == 1)
	{
		if (game->player->x + x >= game->player->target_x)
		{
			game->player_dir = 0;
			x = 0;
		}
		draw_animation(game->assests[4]->animations->next->next->next->next, (game->player->x + x) * IMG_WIDTH,
			game->player->y * IMG_HEIGHT, game->assests[0]->mlx, game->assests[0]->win);
		x += 10;
	}
	else
		draw_animation(game->assests[4]->animations, game->player->x * IMG_WIDTH,
			game->player->y * IMG_HEIGHT, game->assests[0]->mlx, game->assests[0]->win);
}



int draw_map(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	y = 0;
	get_player_xy(game);
	while (game->map[i])
	{
		j = 0;
		x = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_sprite(game->assests[1], x, y);
			else if (game->map[i][j] != '1')
				draw_sprite(game->assests[0], x, y);
			if (game->map[i][j] == 'P')
				draw_player(game);
			else if (game->map[i][j] == 'C')
				draw_sprite(game->assests[2], x, y);
			else if (game->map[i][j] == 'E')
				draw_sprite(game->assests[3], x, y);
			j++;
			x += IMG_WIDTH;
		}
		y += IMG_HEIGHT;
		i++;
	}
	mlx_clear_window(game->assests[0]->mlx, game->assests[0]->win);
	mlx_put_image_to_window(game->assests[0]->mlx, game->assests[0]->win, game->screen->img_ptr, 0, 0);
	return (0);
}
