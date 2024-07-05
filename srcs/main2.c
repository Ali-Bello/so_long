/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:40:21 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/04 14:28:40 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	load_assests(t_game *game)
{
	game->assests[0] = new_sprite("textures/Ground24.xpm", game->mlx,
			game->win);
	load_animations(game->assests[0], 1);
	game->assests[1] = new_sprite("textures/Walls.xpm", game->mlx, game->win);
	load_animations(game->assests[1], 1);
	game->assests[2] = new_sprite("textures/Collectibles.xpm", game->mlx,
			game->win);
	load_animations(game->assests[2], 1);
	game->assests[3] = new_sprite("textures/Exit_64.xpm", game->mlx, game->win);
	load_animations(game->assests[3], 1);
	game->assests[4] = new_sprite("textures/Player_64.xpm", game->mlx,
			game->win);
	load_animations(game->assests[4], 24);
	game->assests[5] = new_sprite("textures/enemy.xpm", game->mlx,
			game->win);
	load_animations(game->assests[5], 1);
}

int	apply_moves(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(1);
	else if (keycode == 100)
		move_player(game, game->player->x + 1, game->player->y);
	else if (keycode == 115)
		move_player(game, game->player->x, game->player->y + 1);
	else if (keycode == 97)
		move_player(game, game->player->x - 1, game->player->y);
	else if (keycode == 119)
		move_player(game, game->player->x, game->player->y - 1);
	return (0);
}

int	stop_moving(int keycode, t_game *game)
{
	if (keycode == 100 || keycode == 115 || keycode == 97 || keycode == 119)
		game->player->is_moving = 0;
	return (0);
}
int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	if (ac < 2)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCAN'T OPEN MAP FILE\n"), -1);
	/**INITIALIZE THE GAME VARIABLES*/
	game.map = get_map(fd);
	game.mlx = mlx_init();
	game.width = IMG_WIDTH * ft_strlen(game.map[0]);
	game.height = IMG_HEIGHT * get_height(game.map);
	if (game.width > 5000 || game.height > 3000)
		return (printf("MAP IS TOO BIG\n"));
	game.win = mlx_new_window(game.mlx, game.width, game.height, "SO LONG");
	game.collectibles = 0;
	game.collected = 0;
	game.moves = 0;
	game.move_delay = 0;
	game.player_dir = -1;
	game.available_positions = malloc(sizeof(char *) * (game.height / IMG_HEIGHT));
	for (int i = 0; i < game.height / IMG_HEIGHT; i++)
		game.available_positions[i] = malloc(sizeof(char) * (game.width / IMG_WIDTH));
	get_position('E', game.map, &game.exit_y, &game.exit_x);
	/********************************/

	/**ASSESTS*/
	game.assests = malloc(sizeof(t_sprite *) * 7);
	game.assests[6] = NULL;
	load_assests(&game);
	/**********/

	/*BACKGROUND IMG*/
	game.bg = malloc(sizeof(t_img));
	if (!game.bg)
		return (free(game.map), 0);
	game.bg->img_ptr = mlx_new_image(game.mlx, game.width, game.height);
	if (!game.bg->img_ptr)
		return (free(game.bg), free(game.map), 0);
	game.bg->width = game.width;
	game.bg->height = game.height;
	game.bg->img_data = mlx_get_data_addr(game.bg->img_ptr, &game.bg->bpp,
			&game.bg->line_len, &game.bg->endian);
	/***************/

	/**PLAYER*/
	game.player = malloc(sizeof(t_player));
	*(game.player) = (t_player){game.assests[4]->animations, NULL, 0, 0, 0, 0, 0, 0,
		0, 0, 0};
	get_player_mapxy(&game);
	/*********/

	/**ENEMY**/
	game.enemy = malloc(sizeof(t_enemy));
	if (!game.enemy)
		return (free(game.map), 0);
	*(game.enemy) = (t_enemy){game.assests[5]->animations, 0, 0, 0, 0, 0, 0, 0};
	spawn_enemy(&game);
	get_position('X', game.map, &game.enemy->y, &game.enemy->x);
	game.enemy->x_px = game.enemy->x * IMG_WIDTH;
	game.enemy->y_px = game.enemy->y * IMG_HEIGHT;
	game.enemy->target_x = game.enemy->x_px;
	game.enemy->target_y = game.enemy->y_px;
	for (int i = 0; game.map[i]; i++)
		printf("[%s]\n", game.map[i]);
	/********/

	render_map(&game);
	mlx_key_hook(game.win, apply_moves, &game);
	mlx_loop_hook(game.mlx, update_player, &game);
	mlx_loop(game.mlx);
}
