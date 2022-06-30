/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:38:30 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 09:37:43 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ut(t_shell *mini)
{
	int		i;
	char	buff[256];
	char	**str;
	char	*temp;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		str = ft_split(mini->tab_save_exp[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			temp = ft_strjoin("PWD=", getcwd(buff, sizeof(buff)));
			free(str[0]);
			str[0] = temp;
			mini->tab_save_exp[i] = ft_strdup(str[0]);
			ft_free(str);
			break ;
		}
		ft_free(str);
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
			ft_free(str);
			return (1);
		}
		ft_free(str);
		i++;
	}
	return (0);
}

void	utils_change_pwd(t_shell *mini, int n, char **str, int i)
{
	char	buff[256];
	char	*temp;
	char	*sec_temp;

	sec_temp = getcwd(buff, sizeof(buff));
	if (sec_temp)
	{
		temp = ft_strjoin("PWD=", sec_temp);
		free(str[0]);
		str[0] = temp;
		if (n > 0)
			free(mini->tab_save_env[i]);
		mini->tab_save_env[i] = ft_strdup(str[0]);
	}
	ft_free(str);
}

void	change_pwd(t_shell *mini)
{
	int			i;
	char		**str;
	static int	n;

	i = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (strcmp(str[0], "PWD") == 0)
		{
			utils_change_pwd(mini, n, str, i);
			break ;
		}
		ft_free(str);
		i++;
	}
	if (mini->tab_save_exp)
		ut(mini);
	n++;
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
			ft_free(temp);
			return (1);
		}
		ft_free(temp);
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
