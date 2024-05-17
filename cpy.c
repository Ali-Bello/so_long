#include "headers/so_long.h"
#include "string.h"

#define IMG_WIDTH 65

void print_pixel_color(char *img_data, int idx, int bpp) {
    unsigned char r, g, blue;
    int color;

    if (bpp == 32) { // 32 bits per pixel (4 bytes)
        color = *(int *)(img_data + idx);
        blue = color & 0xFF;
        g = (color >> 8) & 0xFF;
        r = (color >> 16) & 0xFF;
    } else if (bpp == 24) { // 24 bits per pixel (3 bytes)
        blue = *(img_data + idx);
        g = *(img_data + idx + 1);
        r = *(img_data + idx + 2);
    } else {
        // Handle other bpp formats if needed
        printf("Unsupported bits per pixel format.\n");
        return;
    }

    printf("Pixel color: R=%d, G=%d, B=%d\n", r, g, blue);
}


void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_data + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->img_data
			+ (y * img->line_len) + (x * img->bpp / 8))));
}

void cpy_img(t_img *src, t_img *dst, int x, int y) {
    int i, j;

    i = 0;
    while (i < dst->width)
    {
        j = 0;
        while (j < dst->height)
        {
            my_mlx_pixel_put(dst, i, j, get_pixel_img(src, x + i, y + j));
            j++;
        }
        i++;
    }
}

void print_nxn_pixels(t_img *img, int n) {
    int i, j;
    int idx;

    if (n <= 0) {
        printf("Invalid value of n. It should be greater than 0.\n");
        return;
    }

    for (i = 0; i < img->height && i < n; i++) {
        for (j = 0; j < img->width && j < n; j++) {
            idx = (i * img->line_len) + (j * (img->bpp / 8));
            printf("Pixel at (%d, %d): ", j, i);
            print_pixel_color(img->img_data, idx, img->bpp);
        }
    }
    printf("i = [%d]\n", i);
}

int main()
{
	void	*mlx, *win;
	t_img	src, dst;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 900, 900, "test");
	src.img_ptr = mlx_xpm_file_to_image(mlx, "textures/Player.xpm", &src.width, &src.height);
	src.img_data = mlx_get_data_addr(src.img_ptr, &src.bpp, &src.line_len, &src.endian);
	dst.img_ptr = mlx_new_image(mlx, 500, 500);
	dst.width = 500;
	dst.height = 500;
	dst.img_data = mlx_get_data_addr(dst.img_ptr, &dst.bpp, &dst.line_len, &dst.endian);
    cpy_img(&src, &dst, 0, 0);
	mlx_put_image_to_window(mlx, win, dst.img_ptr, 0, 0);
	mlx_loop(mlx);
}
