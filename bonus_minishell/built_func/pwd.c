/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:55 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 03:53:49 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ft_pwd(int fd)
{
	char	buff[256];

	ft_putendl_fd(getcwd(buff, sizeof(buff)), fd);
}

int	loop(t_shell *mini)
{
	int		i;
	char	**temp;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		temp = ft_split(mini->tab_save_exp[i], '=');
		if (ft_strcmp(temp[0], "HOME") == 0)
		{
			chdir(temp[1]);
			ft_free(temp);
			return (1);
		}
		ft_free(temp);
		i++;
	}
	return (0);
}

void	ft_13(t_shell *index, char *str, char **save, char **temp)
{
	static int	n;

	norme4(index, temp, str, save);
	if (index->tab_save_exp)
		unset_exp(index, str);
	g_id.g_status_exec = 0;
	if (n > 0)
		ft_free(temp);
	else
		free(temp);
	n++;
}

int	no(t_shell *index, char *add_str, char *string, int i)
{
	char	**temp;
	char	**sec_temp;

	temp = ft_split(string, '=');
	sec_temp = ft_split(add_str, '=');
	if (ft_strcmp(temp[0], sec_temp[0]) == 0)
	{
		free(index->tab_save_exp[i]);
		index->tab_save_exp[i] = ft_strdup(add_str);
		ft_free(temp);
		ft_free(sec_temp);
		return (3);
	}
	ft_free(temp);
	ft_free(sec_temp);
	return (0);
}

int	no1(t_shell *index, char *add_str, char *string, int i)
{
	char	**sec_temp;

	sec_temp = ft_split(add_str, '=');
	if (ft_strcmp(sec_temp[0], string) == 0)
	{
		free(index->tab_save_exp[i]);
		index->tab_save_exp[i] = ft_strdup(add_str);
		ft_free(sec_temp);
		return (5);
	}
	ft_free(sec_temp);
	return (0);
}
