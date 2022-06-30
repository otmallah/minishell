/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:08:20 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 09:44:56 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

int	ft_arg(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] && str[1] == 'n')
		i++;
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_echo(char **str, int fd)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (ft_arg(str[1]) == 1 && i == 1)
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
		if (ft_arg(str[1]) != 1)
			ft_putstr_fd("\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}

void	old(t_shell *mini, int a)
{
	char	buff[256];

	if (a > 0)
		free(mini->save_old_pwd);
	mini->save_old_pwd = ft_strdup(mini->save_pwd);
	free(mini->save_pwd);
	if (getcwd(buff, sizeof(buff)) != NULL)
		mini->save_pwd = ft_strdup(getcwd(buff, sizeof(buff)));
}
