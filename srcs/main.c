#include "../headers/so_long.h"

int close1(int keycode)
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
	img[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx, "textures/Ground.xpm",
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
	if (keycode == 39)
		move_right(data->map, data->game);
	else if (keycode == 38)
		move_left(data->map, data->game);
	else if (keycode == 40)
		move_up(data->map, data->game);
	else if (keycode == 37)
		move_down(data->map, data->game);
	draw_map(data->map, data->img, data->mlx);
	return (0);
}

// Scale the image using nearest-neighbor interpolation
void scale_image(void *mlx_ptr, void *win_ptr, t_img *img) {

    // Get image information
	img[0].img = mlx_get_data_addr(img[0].img_ptr, &(img[0].bpp), &(img[0].line_len), &(img[0].endian));
    // Iterate through each pixel in the scaled image
    for (int i = 0; i < img[0].width * img[0].scale; i++) {
        for (int j = 0; j < img[0].height * img[0].scale; j++) {
            // Calculate corresponding pixel in original image
            int orig_x = i / img[0].scale;
            int orig_y = j / img[0].scale;

            // Calculate position in image data array
            int index = orig_y * img[0].line_len + orig_x * (img[0].bpp / 8);

            // Get color of original pixel
            int color = *((int *)(img[0].img + index));

            // Plot scaled pixel
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
			// (void)mlx_ptr;
			// (void)win_ptr;
			// (void)color;
        }
    }
}


int main()
{
	t_img	imgs[6];
	t_mlx	mlx;
	char	**map;
	int	fd;

	fd = open("maps/map0.ber", O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCAN'T OPEN MAP FILE\n"), -1);
	map = get_map(fd);
	mlx.mlx = mlx_init();
	load_assests(imgs, &mlx);
	imgs[0].scale = 1;
	if (imgs[0].width * ft_strlen(*map) > 1920 ||
		imgs[0].height * get_height(map) > 1080)
	{
		imgs[0].scale = ((double)1920 / (double)imgs[0].width / (double)ft_strlen(*map));
	//	imgs[0].scale /= ft_strlen(*map);
		printf("scale = [%f]\n", imgs[0].scale);
	}
	int w_width = ft_strlen(*map) * imgs[0].width * imgs[0].scale;
	int	w_height = imgs[0].height * get_height(map) * imgs[0].scale;
	// printf("imgs[0].width = [%d]\timgs[0].height = [%d]\n", imgs[0].width, imgs[0].height);
	// printf("w_width = [%d]\tw_height = [%d]\t scale =[%f]\n", w_width, w_height, imgs[0].scale);
	mlx.window = mlx_new_window(mlx.mlx, w_width,
			w_height, "SO LONG");
	t_game game;
	game.collected = 0;
	game.collectibles = 10;
	game.moves = 0;
	t_data data;
	data.game = &game;
	data.img = imgs;
	data.map = map;
	data.mlx = mlx.mlx;
	mlx_key_hook(mlx.window, close1, mlx.mlx);
	mlx_hook(mlx.window, 17, 0, close_laysa, 0);
	mlx_hook(mlx.window, 2, 0, apply_move, &data);
	scale_image(mlx.mlx, mlx.window, imgs);
	draw_map(map, imgs, &mlx);
	mlx_loop(mlx.mlx);
}

