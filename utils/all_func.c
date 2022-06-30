/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:39:19 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 05:10:21 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*st;

	st = (char *)str;
	i = 0;
	while (st[i])
	{
		if (st[i] == (char)c)
			return (st + i + 1);
		i++;
	}
	if (st[i] == (char)c)
		return (st + i);
	return (NULL);
}

void	ft_putendl_fd(char *s,	int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		write (fd, "\n", 1);
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
