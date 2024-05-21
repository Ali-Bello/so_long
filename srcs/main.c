#include "../headers/so_long.h"

int	close1(int keycode)
{
	if(keycode == 53)
		exit(1);
	return 0;
}
int	close_laysa()
{
	return (exit(0), 0);
}
void	load_assests(t_sprite *sprites, t_mlx *mlx)
{
	sprites[0] = *new_sprite("../textures/Player.xpm", mlx->mlx, mlx->window);
		load_animations(&sprites[0], 1);
	sprites[1] = *new_sprite("../textures/Player.xpm", mlx->mlx, mlx->window);
		load_animations(&sprites[1], 2);
	sprites[2] = *new_sprite("../textures/Player.xpm", mlx->mlx, mlx->window);
		load_animations(&sprites[2], 1);
	sprites[3] = *new_sprite("../textures/Player.xpm", mlx->mlx, mlx->window);
		load_animations(&sprites[3], 2);
	sprites[4] = *new_sprite("../textures/Player.xpm", mlx->mlx, mlx->window);
		load_animations(&sprites[4], 5);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

// int	apply_move(int keycode, t_data *data)
// {
// 	if (keycode == 2)
// 		move_right(data->map, data->game);
// 	else if (keycode == 0)
// 		move_left(data->map, data->game);
// 	else if (keycode == 13)
// 		move_up(data->map, data->game);
// 	else if (keycode == 1)
// 		move_down(data->map, data->game);
// 	draw_map(data->map, data->img, data->mlx);
// 	return (0);
// }

int main()
{
	t_sprite	sprites[6];
	t_mlx	mlx;
	char	**map;
	int	fd;

	fd = open("maps/map1.ber", O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCAN'T OPEN MAP FILE\n"), -1);
	map = get_map(fd);
	mlx.mlx = mlx_init();
	mlx.width = IMG_WIDTH * ft_strlen(*map);
	mlx.height = IMG_HEIGHT * get_height(map);
	if (mlx.width > 5000 || mlx.height > 3000)
		return (printf("MAP IS TOO BIG\n"));
	// if (mlx.width > SCREEN_WIDTH || mlx.height > SCREEN_HEIGHT)
	// 	scale_assests(&mlx, imgs, ft_strlen(*map), get_height(map));
	mlx.window = mlx_new_window(mlx.mlx, mlx.width ,mlx.height, "SO LONG");
	load_assests(sprites, &mlx);
	mlx_key_hook(mlx.window, close1, mlx.mlx);
	mlx_hook(mlx.window, 17, 0, close_laysa, 0);
	// mlx_hook(mlx.window, 2, 0, apply_move, &data);
	draw_map(map, sprites);
	mlx_loop(mlx.mlx);
}
