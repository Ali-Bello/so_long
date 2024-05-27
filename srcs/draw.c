/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:18:01 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/27 01:47:46 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	draw_sprite(t_sprite *sprite, int x, int y)
{
	static t_frame	*current_frame;
	t_frame	*tmp_frame;
	int				i;

	if (!sprite || !sprite->animations)
		return (0);
	if (sprite->animations->frame_idx == 0)
		current_frame = sprite->animations->frames;
	mlx_clear_window(sprite->mlx, sprite->win);
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

void	get_animation(t_sprite **sprite, int idx)
{
	int	i;

	i = 0;
	while (i < idx && (*sprite)->animations)
		(*sprite)->animations = (*sprite)->animations->next;
}

void draw_player(t_game *game)
{
	static t_animation *tmp;
	static int	current_x;
	static int	current_y;

	tmp = game->assests[4]->animations;
	if (!current_x && !current_y)
	{
		current_x = game->player->x * IMG_WIDTH + game->player->dx;
		current_y = game->player->y * IMG_HEIGHT + game->player->dy;
		game->assests[4]->animations = game->assests[4]->animations->next->next->next->next;
	}
	if (game->player->moving)
	{
		printf("x = [%d]\t y = [%d]\n", current_x, current_y);
		draw_sprite(game->assests[4], current_x, current_y);
		current_x += game->player->dx;
		current_y += game->player->dy;
		printf("target_x = [%d]\ttarget_y = [%d]\n", game->player->target_x * IMG_WIDTH, game->player->target_y * IMG_HEIGHT);
		if (current_x >= game->player->target_x * IMG_WIDTH && current_y >= game->player->target_y * IMG_HEIGHT)
		{
			game->assests[4]->animations = tmp;
			game->player->x = game->player->target_x;
			game->player->y = game->player->target_y;
			game->player->moving = 0;
			draw_sprite(game->assests[4], current_x, current_y);
		}
	}
	else
		draw_sprite(game->assests[4], game->player->x * IMG_WIDTH, game->player->y * IMG_HEIGHT);
}


int draw_map(t_game *game)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	y = 0;
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
			if (game->map[i][j] == 'C')
				draw_sprite(game->assests[2], x, y);
			if (game->map[i][j] == 'E')
				draw_sprite(game->assests[3], x, y);
			j++;
			x += IMG_WIDTH;
		}
		y += IMG_HEIGHT;
		i++;
	}
	return (0);
}
