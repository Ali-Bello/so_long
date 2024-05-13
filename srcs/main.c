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
void	load_assests(t_img *img, t_mlx *mlx)
{
	img[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx, "textures/skulls2.xpm",
				&(img[0].width), &(img[0].height));
	img[1].img_ptr = mlx_xpm_file_to_image(mlx->mlx, "textures/floor.xpm",
				&(img[1].width), &(img[1].height));
	img[2].img_ptr = mlx_xpm_file_to_image(mlx->mlx, "textures/sorcier3.xpm",
				&(img[2].width), &(img[2].height));
	img[3].img_ptr = mlx_xpm_file_to_image(mlx->mlx, "textures/gem.xpm",
				&(img[3].width), &(img[3].height));
	img[4].img_ptr = mlx_xpm_file_to_image(mlx->mlx, "textures/Door.xpm",
				&(img[4].width), &(img[4].height));
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	apply_move(int keycode, t_data *data)
{
	if (keycode == 2)
		move_right(data->map, data->game);
	else if (keycode == 0)
		move_left(data->map, data->game);
	else if (keycode == 13)
		move_up(data->map, data->game);
	else if (keycode == 1)
		move_down(data->map, data->game);
	draw_map(data->map, data->img, data->mlx);
	return (0);
}

int main()
{
	t_img	imgs[6];
	t_mlx	mlx;
	char	**map;
	int	fd;

	fd = open("maps/map1.ber", O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCAN'T OPEN MAP FILE\n"), -1);
	map = get_map(fd);
	mlx.mlx = mlx_init();
	load_assests(imgs, &mlx);
	mlx.width = imgs[0].width * ft_strlen(*map);
	mlx.height = imgs[0].height * get_height(map);
	// if (mlx.width > 2500 * 2 || mlx.height > 1500 * 2)
	// 	return (printf("MAP IS TOO BIG\n"));
	// if (mlx.width > SCREEN_WIDTH || mlx.height > SCREEN_HEIGHT)
	// scale_assests(&mlx, imgs, ft_strlen(*map), get_height(map));
	mlx.window = mlx_new_window(mlx.mlx, mlx.width ,mlx.height, "SO LONG");
	t_game game;
	game = (t_game){10, 0, 0};
	t_data data;
	data = (t_data){&game, map, imgs, mlx.mlx};
	mlx_key_hook(mlx.window, close1, mlx.mlx);
	mlx_hook(mlx.window, 17, 0, close_laysa, 0);
	mlx_hook(mlx.window, 2, 0, apply_move, &data);
	draw_map(map, imgs, &mlx);
	mlx_loop(mlx.mlx);
}

