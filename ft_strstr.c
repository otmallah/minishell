/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 11:43:54 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 04:37:35 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strstr(char *str, char *to_find, int size)
{
	int	i;
	int	j;
    int a;

	i = 0;
	j = 0;
    a = 0;
	if (*to_find == '\0')
		return (str);
	i = ft_strlen(str);
	while (i >= 0)
	{
		while (to_find[j] == str[i + j] && a == size )
		{
			return (&str[i]);
		}
		if (a == size)
			return 0;
		j = 0;
		i--;
        a++;
	}
	return (0);
}

char	*ft_strstr3(char *str, char *to_find, int size)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return (str);
	k = ft_strlen(str);
	while(i < size)
		i++;
	while (str[i] && (i + size) != k)
	{
		while (to_find[j] == str[i + j] && (i + size) != k)
		{
			if (to_find[j + 1] == '\0')
			{
				return (&str[i]);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_strstr2(char *str, char *to_find, int size)
{
	int	i;
	int	j;
    int a;

	i = 0;
	j = 0;
    a = 0;
	if (*to_find == '\0')
		return (str);
	while (str[i])
	{
        a++;
		while (to_find[j] == str[i + j] && i < size)
		{
			if (to_find[j + 1] == '\0')
			{
				return (&str[i]);
			}
			j++;
		}
		if (i < size)
			return 0;
		j = 0;
		i++;
	}
	return (0);
}

