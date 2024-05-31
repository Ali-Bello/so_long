// File: animation.c
#include "headers/so_long.h"
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data {
    void    *mlx;
    void    *win;
	void	*bg;
	t_sprite *player;
	t_frame	*current_frame;
    int     img_width;
    int     img_height;
    int     x;
    int     y;
    int     dest_x;
    int     dest_y;
}               t_data;

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

int update_positions(t_data *data)
{
    if (data->x < data->dest_x)
        data->x += 4;
    if (data->x > data->dest_x)
        data->x -= 4;
    if (data->y < data->dest_y)
        data->y += 4;
    if (data->y > data->dest_y)
        data->y -= 4;
    draw_animation(data->player->animations->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next,
				data->x, data->y);
    if (data->x == data->dest_x && data->y == data->dest_y)
        return 0;
    return 1;
}

int	draw(t_data *data)
{
	for (int x = 100; x < 800; x += 50)
		mlx_put_image_to_window(data->mlx, data->win, data->bg, x, 100);
	update_positions(data);
    mlx_do_sync(data->mlx);

	return (0);
}
int main()
{
	t_data  data;
	int width;
	int height;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, 800, 600, "Animation Example");

	data.player = new_sprite("textures/15.xpm", data.mlx, data.win);
		load_animations(data.player, 24);
    // Load the XPM image
	data.player->animations->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->frame_delay = 3;
	data.x = 100;      // Starting x coordinate
    data.y = 100;      // Starting y coordinate
    data.dest_x = 200; // Destination x coordinate
    data.dest_y = 100; // Destination y coordinate
	data.bg = mlx_xpm_file_to_image(data.mlx, "textures/stone.xpm", &width, &height);
	// while (update_positions(&data))
        // mlx_do_sync(data.mlx);
	mlx_loop_hook(data.mlx, draw, &data);
	mlx_loop(data.mlx);
    return (0);
}

