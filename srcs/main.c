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
void	load_assests(t_sprite **sprites, t_mlx *mlx)
{
	sprites[0] = new_sprite("textures/Free_space.xpm", mlx->mlx, mlx->window);
		load_animations(sprites[0], 1);
	sprites[1] = new_sprite("textures/Walls.xpm", mlx->mlx, mlx->window);
		load_animations(sprites[1], 2);
	sprites[2] = new_sprite("textures/Collectibles.xpm", mlx->mlx, mlx->window);
		load_animations(sprites[2], 1);
	sprites[3] = new_sprite("textures/Exit.xpm", mlx->mlx, mlx->window);
		load_animations(sprites[3], 2);
	sprites[4] = new_sprite("textures/Player2.xpm", mlx->mlx, mlx->window);
		load_animations(sprites[4], 24);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
#include <time.h>

int	apply_moves(int keycode, t_game *game)
{
	get_player_xy(game);
	if (keycode == 2)
		right_move(game);
	else if (keycode == 1)
		down_move(game);
	else if (!keycode)
		left_move(game);
	else if (keycode == 13)
		up_move(game);
	if (!keycode || keycode == 1 || keycode == 2 || keycode == 13)
	{
		game->player->dx = ((game->player->target_x - game->player->x) * IMG_WIDTH) / 6.0;
		game->player->dy = ((game->player->target_y - game->player->y) * IMG_HEIGHT) / 6.0;
		game->player->moving = 1;
	}
	return (0);
}

int main()
{
	t_sprite	*sprites[6];
	t_mlx	mlx;
	t_game	game;
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
	mlx.window = mlx_new_window(mlx.mlx, mlx.width ,mlx.height, "SO LONG");
	load_assests(sprites, &mlx);
	t_player ptr = (t_player){sprites[4]->animations, sprites[4]->animations->frames, 0, 0, 0, 0, 0, 0, 0};
	game = (t_game){sprites, &ptr, map, 17, 0, 0};
	get_player_xy(&game);
	mlx_key_hook(mlx.window, apply_moves, &game);
	// mlx_key_hook(mlx.window, close1, mlx.mlx);
	mlx_hook(mlx.window, 17, 0, close_laysa, 0);
	mlx_loop_hook(mlx.mlx, draw_map, &game);
	mlx_loop(mlx.mlx);
}
