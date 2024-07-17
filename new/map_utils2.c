/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:58:48 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 03:58:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	open_file(char *name, int *error_code)
{
	int	fd;

	if (ft_strncmp(name + ft_strlen(name) - 4, ".ber", 4))
	{
		*error_code = -1;
		return (-1);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
		*error_code = 2;
	return (fd);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**duplicate_map(char **map)
{
	int		i;
	char	**dup;

	dup = malloc(sizeof(char *) * (get_height(map) + 1));
	i = 0;
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1')
		return ;
	map[y][x] = '1';
	flood_fill(map, x + 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y - 1);
}

void	get_position(char c, char **map, int *y, int *x)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				break ;
			j++;
		}
		if (map[i][j] == c)
			break ;
		i++;
	}
	*y = i;
	*x = j;
}
