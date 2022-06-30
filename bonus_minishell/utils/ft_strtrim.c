/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:38:19 by otmallah          #+#    #+#             */
/*   Updated: 2022/05/20 20:41:47 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

typedef struct s_cal {
	int		i;
	int		a;
	int		j;
	int		k;
	char	*sec;
}	t_cal;

static int	first_string(char *str, char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && s[j])
	{
		if (str[i] == s[j])
		{
			i++;
			j = -1;
		}
		j++;
	}
	return (i);
}

static int	end_string(char *str, char const *s)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = 0;
	while (s[j])
	{
		if (str[i] == s[j])
		{
			i--;
			j = -1;
		}
		j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	t_cal	index;

	if (!s1 || !set)
		return (NULL);
	if (s1 != NULL)
	{
		index.i = first_string((char *)s1, set);
		index.j = end_string((char *)s1, set);
		index.k = index.j - index.i + 1;
		if (index.k < 0)
			index.k = 0;
		index.sec = (char *)malloc(sizeof(char) * (index.k + 1));
		if (!index.sec)
			return (NULL);
		index.a = 0;
		while (index.a < index.k)
		{
			index.sec[index.a] = ((char *)s1)[index.i];
			index.a++;
			index.i++;
		}
		index.sec[index.a] = '\0';
	}
	return (index.sec);
}
