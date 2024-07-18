/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:16:06 by aderraj           #+#    #+#             */
/*   Updated: 2024/07/04 13:05:16 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

static size_t	count(const char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	flag;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		flag = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > flag)
			count++;
	}
	return (count);
}

static char	**free_all(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

static char	**fill(char **ptr, const char *s, char c)
{
	size_t	i;
	size_t	flag;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		flag = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > flag)
		{
			ptr[j] = ft_substr(s, flag, i - flag);
			if (ptr[j] == NULL)
				return (free_all(ptr));
			j++;
		}
	}
	ptr[j] = NULL;
	free((void *)s);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = malloc(sizeof(char *) * (count(s, c) + 1));
	if (!ptr)
		return (NULL);
	return (fill(ptr, s, c));
}
