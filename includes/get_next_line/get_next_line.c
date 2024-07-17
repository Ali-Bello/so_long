/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:24:52 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/06 01:21:11 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

int	line_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*line_extract(char **buffer)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	if (!*buffer)
		return (NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	i += (*buffer)[i] == '\n';
	line = ft_substr(*buffer, 0, i);
	if (!line)
	{
		free(*buffer);
		return (free(line), NULL);
	}
	tmp = ft_strdup(*buffer + i);
	free(*buffer);
	*buffer = 0;
	if (tmp && *tmp)
		*buffer = ft_strdup(tmp);
	free(tmp);
	return (line);
}

int	read_check(int fd, char **buffer)
{
	if (read(fd, 0, 0) < 0)
	{
		if (*buffer && (*buffer)[0])
		{
			free(*buffer);
			*buffer = 0;
		}
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp;
	ssize_t		bytes;

	if (fd < 0 || read_check(fd, &buffer))
		return (NULL);
	tmp = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	bytes = read(fd, tmp, BUFFER_SIZE);
	if (bytes >= 0)
		tmp[bytes] = 0;
	if (bytes > 0)
	{
		while (!line_check(tmp) && bytes)
		{
			buffer = ft_strjoin(buffer, tmp);
			ft_bzero(tmp, ((size_t)BUFFER_SIZE + 1));
			bytes = read(fd, tmp, BUFFER_SIZE);
		}
		if (line_check(tmp))
			buffer = ft_strjoin(buffer, tmp);
	}
	return (free(tmp), line_extract(&buffer));
}
