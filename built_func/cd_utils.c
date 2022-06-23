/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:38:30 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/22 23:46:04 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ut(t_shell *mini)
{
	int		i;
	int		j;
	char	buff[256];
	char	**str;
	char	*temp;

	i = 0;
	j = 0;
	while (mini->tab_save_exp[i])
	{
		str = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			temp = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
			free(str[0]);
			str[0] = temp;
			mini->tab_save_exp[i] = strdup(str[0]);
			while (str[j])
				free(str[j++]);
			break;
		}
		while (str[j])
			free(str[j++]);
		j = 0;
		i++;
	}
}

int	ut2(t_shell *mini, int a)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	while (mini->tab_save_exp[i])
	{
		str = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(str[0], "HOME") == 0)
		{
			if (a == 2)
				ft_putstr_fd(str[1], 1);
			else
				chdir(str[1]);
			while (str[j])
				free(str[j++]);
			return (1);
		}
		while (str[j])
			free(str[j++]);
		i++;
	}
	return (0);
}

void	change_pwd(t_shell *mini)
{
	int		i;
	int		j;
	char	**str;
	char	buff[256];
	char	*temp;
	static int n;

	i = 0;
	j = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			temp = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
			free(str[0]);
			str[0] =temp;
			if (n > 0)
				free(mini->tab_save_env[i]);
			mini->tab_save_env[i] = strdup(str[0]);
			ft_free(str);
			break;
		}
		ft_free(str);
		j = 0;
		i++;
	}
	if (mini->tab_save_exp)
		ut(mini);
	n++;
}

int	search_path_in_env(t_shell *mini, int a)
{
	int		i;
	int		j;
	char	**str;
	int		k;

	i = 0;
	j = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "HOME") == 0)
		{
			if (a == 2)
				ft_putstr_fd(str[1], 1);
			else
				chdir(str[1]);
			ft_free(str);
			return (1);
		}
		ft_free(str);
		j = 0;
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
	int		j;
	char	**temp;

	j = 0;
	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(temp[0], "HOME") == 0)
		{
			chdir(temp[1]);
			ft_free(temp);
			return (1);
		}
		ft_free(temp);
		j = 0;
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
