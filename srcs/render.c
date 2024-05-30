/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:39:30 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/30 01:08:35 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

void draw_animation(t_animation *animation, int x, int y)
{
	if (!animation || !animation->frames)
		return;
	if (animation->frame_idx == 0)
		animation->current_frame = animation->frames;
	if (animation->current_frame && animation->current_frame->img)
		mlx_put_image_to_window(animation->mlx, animation->win, animation->current_frame->img->img_ptr, x, y);
	animation->delay_counter++;
	if (animation->delay_counter >= animation->frame_delay)
	{
		animation->delay_counter = 0;
		animation->frame_idx++;
		animation->frame_idx = (animation->frame_idx + 1) % animation->frame_count;
		animation->current_frame = animation->frames;
		for (int i = 0; i < animation->frame_idx; i++) {
			if (animation->current_frame->next)
			animation->current_frame = animation->current_frame->next;
		}
	}
}

int	draw_sprite(t_sprite *sprite, int x, int y)
{
	t_frame	*tmp_frame;
	int				i;

	if (!sprite || !sprite->animations)
		return (0);
	if (sprite->animations->frame_idx == 0)
		sprite->animations->current_frame = sprite->animations->frames;
	mlx_put_image_to_window(sprite->mlx, sprite->win, sprite->animations->current_frame->img->img_ptr, x, y);
	sprite->animations->delay_counter++;
	if (sprite->animations->delay_counter >= sprite->animations->frame_delay)
	{
		sprite->animations->delay_counter = 0;
		sprite->animations->frame_idx++;
		sprite->animations->frame_idx = (sprite->animations->frame_idx + 1) % sprite->animations->frame_count;
		i = 0;
		tmp_frame = sprite->animations->frames;
		while (i < sprite->animations->frame_idx)
		{
			tmp_frame = tmp_frame->next;
			i++;
		}
		sprite->animations->current_frame = tmp_frame;
	}
	return 0;
}

void render_player(t_game *game, int x, int y)
{
	t_animation	*player_animation;

	if (!game->player_dir)
		player_animation = game->assests[4]->animations->next->next->next->next->next->next;
	else if (game->player_dir == 1)
		player_animation = game->assests[4]->animations->next->next->next;
	else if (game->player_dir == 2)
		player_animation = game->assests[4]->animations->next->next->next->next->next;
	else if (game->player_dir == 3)
		player_animation = game->assests[4]->animations->next;
	else
		player_animation = game->assests[4]->animations;
	draw_animation(player_animation, x, y);
}

void	render_img(t_game *game, char c, int x, int y)
{
	if (c == '1')
		draw_sprite(game->assests[1], x, y);
	else if (c != '1')
		mlx_put_image_to_window(game->assests[0]->mlx, game->assests[0]->win,
			game->assests[0]->img->img_ptr, x, y);
	if (c == 'P')
		render_player(game, x, y);
	else if (c == 'C')
		draw_sprite(game->assests[2], x, y);
	else if (c == 'E')
		draw_sprite(game->assests[3], x, y);
}

int	render_map(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	get_player_xy(game);
	mlx_clear_window(game->assests[0]->mlx, game->assests[0]->win);
	while (game->map[i])
	{
		j = 0;
		x = 0;
		while (game->map[i][j])
		{
			render_img(game, game->map[i][j], x, y);
			x += IMG_WIDTH;
			j++;
		}
		y += IMG_HEIGHT;
		i++;
	}
	return (0);
}
