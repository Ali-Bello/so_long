/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:51:48 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/03 00:00:10 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

int	is_unique(char **map, char c)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				if (!flag)
					flag = 1;
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	has_collectible(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i + 1])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_rectangular(char **map)
{
	int	i;

	i = 0;
	while (map[i + 1])
	{
		if (ft_strlen(map[i]) != ft_strlen(map[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	is_border(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (0);
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
void	flood_fill(char **map, int x, int y)
{
  if (map[y][x] == '1')
    return;
  map[y][x] = '1';
  flood_fill(map, x + 1, y);
  flood_fill(map, x, y + 1);
  flood_fill(map, x - 1, y);
  flood_fill(map, x, y - 1);
}

void	get_position(char c, char **map, int *y, int *x)
{
	int			i;
	int			j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				break;
			j++;
		}
		if (map[i][j] == c)
				break;
		i++;
	}
	*y = i;
	*x = j;
}

int	path_check(char **map)
{
	int			i;
	int			j;
	char	**dup;

	/** duplicate the map **/
	dup = malloc(sizeof(char *) * (get_height(map) + 1));
	i = 0;
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		i++;
	}
	dup[i] = NULL;

	/** get player coordinates **/
	get_position('P', dup, &i, &j);

	/** fill the map with DFS **/
	flood_fill(dup, j, i);

	/** check if the path is valid**/
	i = 0;
	while (dup[i])
	{
		if (!is_valid_chars(dup, "01"))
			return (0);
		i++;
	}

	/** free the duplicate map **/
	i = 0;
	while (dup[i])
	{
		free(dup[i]);
		i++;
	}
	free(dup);
	return (1);
}

void	map_check(char **map)
{
	if (!map)
		return ;
	if (!is_valid_chars(map, "01CEP"))
		printf("Error\nTHE MAP CONTAINS INVALID CHARACTERS\n");
	else if (!is_enclosed(map))
		printf("Error\nTHE MAP IS NOT ENCLOSED WITH WALLS\n");
	else if (!is_rectangular(map))
		printf("Error\nTHE MAP IS NOT RECATNGULAR\n");
	else if (!is_unique(map, 'E'))
		printf("Error\nTHE MAP CONTAINS MORE THAN ONE EXIT\n");
	else if (!is_unique(map, 'P'))
		printf("Error\nTHE MAP CONTAINS MORE THAN ONE START POSITION\n");
	else if (!has_collectible(map))
		printf("Error\nTHE MAP CONTAINS NO COLLECTIBLE\n");
	else if (!path_check(map))
		printf("Error\nTHE MAP CONTAINS NO PATH TO THE EXIT\n");
	else
	{
		printf("MAP IS VALID\n");
		return ;
	}
	exit(-1);
}

int	new_line_check(char *str)
{
	int	i;

	i = 0;
	if (*str == '\n')
		return (0);
	while (str[i])
		i++;
	if (str[i - 1] == '\n' && str[i - 2] == '\n')
		return (0);
	return (1);
}

char	**get_map(int fd)
{
	char	**map;
	char	*buffer;
	char	*line;

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
			printf("Error\nMAP CONTAINS INVALID CHARS\n");
			exit(-1);
		}
		buffer = ft_strjoin(buffer, line);
		free(line);
	}
	map = ft_split(buffer, '\n');
	return (map_check(map), map);
}
