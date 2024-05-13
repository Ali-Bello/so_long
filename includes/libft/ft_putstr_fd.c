/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:31:35 by aderraj           #+#    #+#             */
/*   Updated: 2024/05/13 16:33:15 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
void	ft_lstiter(t_list *lst, void *mlx, void (*f)(void *, void *))
{
	while (lst && f)
	{
		f(lst->content, mlx);
		lst = lst->next;
	}
}
