// File: animation.c
#include "headers/so_long.h"
#include <stdlib.h>
#include <unistd.h>

int	print_key(int keycode)
{
	printf("keycode = [%d]\n", keycode);
	return (0);
}

int main()
{
	void *mlx, *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 900 ,	 900, "keys");

	mlx_hook(win, 2, 1L<<0, print_key, NULL);
	mlx_loop(mlx);
    return (0);
}

