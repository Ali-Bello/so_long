#include <stdlib.h>
#include <stdio.h>
#include <mlx.h>

#define SCALE_FACTOR 4 // Scale factor (e.g., double the size)
#define ORIGINAL_WIDTH 65 // Original image width
#define ORIGINAL_HEIGHT 65 // Original image height
#define SCALED_WIDTH (ORIGINAL_WIDTH * SCALE_FACTOR) // Scaled image width
#define SCALED_HEIGHT (ORIGINAL_HEIGHT * SCALE_FACTOR) // Scaled image height

typedef struct s_img
{
	void	*img_ptr;
	char	*img;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// Scale the image using nearest-neighbor interpolation
void scale_image(void *mlx_ptr, void *win_ptr, t_img *img) {
    int x, y; // Size of a line in bytes

    // Get image information
    // Iterate through each pixel in the scaled image
    for (int i = 0; i < SCALED_WIDTH; i++) {
        for (int j = 0; j < SCALED_HEIGHT; j++) {
            // Calculate corresponding pixel in original image
            int orig_x = i / SCALE_FACTOR;
            int orig_y = j / SCALE_FACTOR;

            // Calculate position in image data array
            int index = orig_y * img->line_len + orig_x * (img->bpp / 8);

            // Get color of original pixel
            int color = *((int *)(img->img + index));

            // Plot scaled pixel
            mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
        }
    }
}

int main() {
    void *mlx_ptr;
    void *win_ptr;
	t_img	img;
	int	x, y;
    // Initialize Minilibx
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, SCALED_WIDTH, SCALED_HEIGHT, "Scaled Image");

    // Load image (you need to implement this)
   img.img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/Door.xpm", &x, &y);
    if (img.img_ptr == NULL) {
        printf("Error: Failed to load image.\n");
        return EXIT_FAILURE;
    }

    // Get image data
    c

    // Scale the image
    scale_image(mlx_ptr, win_ptr, &img);

    mlx_loop(mlx_ptr);

    return 0;
}

