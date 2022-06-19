/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:29:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/11 13:50:43 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin2(char *str, char c)
{
	int		i;
	int		size;
	char	*ptr;

	i = 0;
	size = ft_strlen(str);
	ptr = malloc(size + 2);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	if (c == '\n')
	{
		ptr[i] = '\0';
		free(str);
		return (ptr);
	}
	ptr[i] = c;
	ptr[i + 1] = '\0';
	free(str);
	return (ptr);
}

char	*get_next_line(int fd)
{
	char	*str;
	char	buff;
	int		rd;

	rd = read(fd, &buff, 1);
	str = ft_strdup("");
	while (rd > 0)
	{
		str = ft_strjoin2(str, buff);
		if (buff == '\n')
			break ;
		rd = read(fd, &buff, 1);
	}
	if (rd < 0)
	{
		free(str);
		return (NULL);
	}
	if (rd == 0 && str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}
