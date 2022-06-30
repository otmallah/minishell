/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:52:40 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 04:38:18 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

char	*ft_getenv(t_shell *m, char *str)
{
	int		j;
	int		i;
	char	*temp;

	i = 0;
	j = 0;
	while (m->tab_save_env[j])
	{
		temp = ft_substr(m->tab_save_env[j], 0, len(m->tab_save_env[j]));
		if (ft_strcmp(temp, str) == 0)
		{
			free(temp);
			return (ft_strchr(m->tab_save_env[j], '='));
		}
		free(temp);
		j++;
	}
	if (m->tab_save_exp)
		return (ft_getenv_utils(m, str));
	return (NULL);
}

void	ft_check_cmd(t_shell *mini, t_list *lst)
{
	DIR	*dp;

	dp = NULL;
	if (lst->val[0][0] == '.')
	{
		dp = opendir(lst->val[0]);
		if ((int)dp != 0)
		{
			printf("minishell: ./exec: is a directory\n");
			exit(126);
		}
		else if (access(lst->val[0], F_OK | X_OK) == 0)
		{
			execve(lst->val[0], &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		else
		{
			write (2, lst->val[0], ft_strlen(lst->val[0]));
			write (2, " :no such file or directory\n", 29);
			exit(127);
		}
	}
	else
		ft_check_cmd_if_exists(mini, lst, dp);
}

char	*utils_path_if_exi(t_shell *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		temp = ft_substr(mini->tab_save_exp[i], 0, len(mini->tab_save_exp[i]));
		if (ft_strcmp(temp, "PATH") == 0)
		{
			free(temp);
			return (ft_strchr(mini->tab_save_exp[i], '='));
		}
		free(temp);
		i++;
	}
	return (NULL);
}

void	ft_err(char *str)
{
	write(2, str, ft_strlen(str));
	write (2, " :command not found\n", 20);
	exit(127);
}

void	ft_execve(char **temp, t_shell *mini, t_list *lst)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	while (temp[i])
	{
		size = ft_strlen(temp[i]);
		temp[i] = ft_h_strjoin(temp[i], "/");
		str = ft_h_strjoin(temp[i], lst->val[0]);
		if (access(str, F_OK) == 0)
		{
			free(temp);
			execve(str, &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		free(str);
		i++;
	}
	free(temp);
}
