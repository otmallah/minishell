/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:06:48 by otmallah          #+#    #+#             */
/*   Updated: 2022/05/23 17:07:00 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static char	convert(int n, char *c, int i)
{
	long int	g;

	g = n;
	if (n == 0)
		c[0] = 48;
	if (n < 0)
	{
		c[0] = '-';
		g *= -1;
	}
	while (i >= 0 && g > 0)
	{
		c[i] = g % 10 + 48;
		g /= 10 ;
		i--;
	}
	return (*c);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		i;
	int		t;

	t = n;
	i = 0;
	if (t < 0)
	{
		t *= -1;
		i++;
	}
	if (t == 0)
		i = 1;
	while (t != 0)
	{
		t /= 10;
		i++;
	}
	string = (char *)ft_calloc(sizeof(char), i + 1);
	if (!string)
		return (NULL);
	i--;
	convert(n, string, i);
	return (string);
}
