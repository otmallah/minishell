/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:01:55 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 00:23:13 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_pwd(int fd)
{
	char	buff[256];

	ft_putendl_fd(getcwd(buff, sizeof(buff)), fd);
}

int	loop(t_shell *mini)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	while (mini->tab_save_exp[i])
	{
		temp = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(temp[0], "HOME") == 0)
		{
			chdir(temp[1]);
			while(temp[j])
				free(temp[j++]);
			return (1);
		}
		while(temp[j])
			free(temp[j++]);
		j = 0;
		i++;
	}
	return (0);
}

void	ft_13(t_shell *index, char *str, char **save, char **temp)
{
	norme4(index, temp, str, save);
	if (index->tab_save_exp)
		unset_exp(index, str);
	g_status_exec = 0;
}

int	no(t_shell *index, char *add_str, char *string, int i)
{
	char	**temp;
	char	**sec_temp;
	int k = 0;

	temp = ft_split(string, '=');
	sec_temp = ft_split(add_str, '=');
	if (strcmp(temp[0], sec_temp[0]) == 0)
	{
		index->tab_save_exp[i] = strdup(add_str);
		while (temp[k])
			free(temp[k++]);
		free(temp);
		k = 0;
		while (sec_temp[k])
			free(sec_temp[k++]);
		free(sec_temp);
		return (3);
	}
	return (0);
}

int	no1(t_shell *index, char *add_str, char *string, int i)
{
	char	**sec_temp;
	int		k = 0;

	sec_temp = ft_split(add_str, '=');
	if (strcmp(sec_temp[0], string) == 0)
	{
		index->tab_save_exp[i] = strdup(add_str);
		while (sec_temp[k])
			free(sec_temp[k++]);
		free(sec_temp);
		return (5);
	}
	while (sec_temp[k])
		free(sec_temp[k++]);
	free(sec_temp);
	return (0);
}
