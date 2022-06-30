/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:35:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/05/27 18:50:24 by otmallah         ###   ########.fr       */
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
