/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 03:51:48 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 03:51:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	path_check(char **map)
{
	int			i;
	int			j;
	char	**dup;

	dup = duplicate_map(map);
	get_position('P', dup, &i, &j);
	flood_fill(dup, j, i);
	i = 0;
	while (dup[i])
	{
		if (!is_valid_chars(dup, "01"))
			return (0);
		i++;
	}
	i = 0;
	while (dup[i])
	{
		free(dup[i]);
		i++;
	}
	free(dup);
	return (1);
}
