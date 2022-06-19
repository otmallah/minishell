/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:08:20 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 13:53:12 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_echo(t_shell *mini, char **str, int fd)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_strcmp(str[1], "-n") == 0 && i == 1)
			i++;
		if (str[i])
		{
			write (fd, str[i], ft_strlen(str[i]));
			if (str[i + 1] != NULL)
				write(fd, " ", 1);
			i++;
		}
	}
	if (str[1])
	{
		if (strcmp(str[1], "-n") != 0)
			ft_putstr_fd("\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}
