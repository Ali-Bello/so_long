/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:08:08 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/06 01:21:38 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	len2;
	char	*ptr;

	if (!s1 || !s2)
	{
		if (s1)
			return (s1);
		else if (s2)
			return (ft_strdup(s2));
		else
			return (NULL);
	}
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + len2 + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ft_memcpy(ptr + len, s2, len2);
	free(s1);
	free(s2);
	ptr[len + len2] = 0;
	return (ptr);
}
