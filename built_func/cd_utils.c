/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:38:30 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 19:59:45 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ut(t_shell *mini)
{
	int		i;
	char	buff[256];
	char	**str;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		str = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			str[0] = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
			mini->tab_save_exp[i] = str[0];
		}
		i++;
	}
}

int	ut2(t_shell *mini, int a)
{
	int		i;
	char	**str;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		str = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(str[0], "HOME") == 0)
		{
			if (a == 2)
				ft_putstr_fd(str[1], 1);
			else
				chdir(str[1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	change_pwd(t_shell *mini)
{
	int		i;
	char	**str;
	char	buff[256];

	i = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			str[0] = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
			mini->tab_save_env[i] = str[0];
		}
		i++;
	}
	if (mini->tab_save_exp)
		ut(mini);
}

int	search_path_in_env(t_shell *mini, int a)
{
	int		i;
	char	**str;
	int		k;

	i = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "HOME") == 0)
		{
			if (a == 2)
				ft_putstr_fd(str[1], 1);
			else
				chdir(str[1]);
			return (1);
		}
		i++;
	}
	if (mini->tab_save_exp)
	{
		k = ut2(mini, a);
		if (k == 1)
			return (1);
	}
	return (0);
}

int	go_home(t_shell *mini)
{
	int		i;
	int		k;
	char	**temp;

	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(temp[0], "HOME") == 0)
		{
			chdir(temp[1]);
			return (1);
		}
		i++;
	}
	if (mini->tab_save_exp)
	{
		k = loop(mini);
		if (k == 1)
			return (k);
	}
	return (0);
}
