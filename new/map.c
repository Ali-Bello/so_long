/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:27:54 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 03:27:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	new_line_check(char *str)
{
	int	i;

	i = 0;
	if (*str == '\n')
		return (0);
	while (str[i])
		i++;
	if (i > 2 && str[i - 1] == '\n' && str[i - 2] == '\n')
		return (0);
	return (1);
}

int	is_valid_chars(char **map, char *charset)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(charset, map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_enclosed(char **map)
{
	int	i;
	int	j;

	if (!is_border(*map))
		return (0);
	i = 1;
	while (map[i + 1])
	{
		j = 0;
		if (map[i][j] != '1')
			return (0);
		while (map[i][j])
			j++;
		if (map[i][--j] != '1')
			return (0);
		i++;
	}
	if (!is_border(map[i]))
		return (0);
	return (1);
}

int map_check(t_game *game)
{
	if (!game->map)
		return (game->error_code = 1);
	if (!is_valid_chars(game->map, "01CEP"))
		return (game->error_code = 4);
	else if (!is_enclosed(game->map))
		return (game->error_code = 5);
	else if (!is_rectangular(game->map))
		return (game->error_code = 6);
	else if (!is_unique(game->map, 'E'))
		return (game->error_code = 7);
	else if (!is_unique(game->map, 'P'))
		return (game->error_code = 8);
	else if (!has_collectible(game->map))
		return (game->error_code = 9);
	else if (!path_check(game->map))
		return (game->error_code = 10);
}

int read_map(char *path, t_game *game)
{
    int     fd;
    char    *buffer;
    char    *line;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (game->error_code = 2);

    buffer = NULL;
    while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!new_line_check(line))
		{
			if (buffer)
				free(buffer);
			free(line);
			return (game->error_code = 3);
		}
		buffer = ft_strjoin(buffer, line);
		free(line);
	}
	game->map = ft_split(buffer, '\n');
    return (map_check(game));
}