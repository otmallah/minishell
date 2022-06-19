/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:52:40 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 18:45:36 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*ft_getenv_utils(t_shell *m, char *str)
{
	char	*temp;
	int		j;

	j = 0;
	while (m->tab_save_exp[j])
	{
		temp = ft_substr(m->tab_save_exp[j], 0, len(m->tab_save_exp[j]));
		if (strcmp(temp, str) == 0)
		{
			free(temp);
			return (ft_strchr(m->tab_save_exp[j], '='));
		}
		free(temp);
		j++;
	}
	return (NULL);
}

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
		if (strcmp(temp, str) == 0)
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
	DIR		*dp;

	if (lst->val[0][0] == '.')
	{
		dp = opendir(lst->val[0]);
		if ((int)dp == 512)
			printf("minishell: ./exec: is a directory\n");
		if (access(lst->val[0], F_OK | X_OK) == 0)
		{
			execve(lst->val[0], &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		write (2, lst->val[0], ft_strlen(lst->val[0]));
		write (2, " :no such file or directory\n", 29);
		exit(0);
	}
	else if (lst->val[0][0] == '/')
	{
		if (access(lst->val[0], F_OK) == 0)
		{
			execve(lst->val[0], &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		ft_err(lst->val[0]);
	}
}

char	*utils_path_if_exi(t_shell *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->tab_save_exp[i])
	{
		temp = ft_substr(mini->tab_save_exp[i], 0, len(mini->tab_save_exp[i]));
		if (strcmp(temp, "PATH") == 0)
		{
			free(temp);
			return (ft_strchr(mini->tab_save_exp[i], '='));
		}
		free(temp);
		i++;
	}
	return (NULL);
}

char	*check_path_if_exi(t_shell *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_substr(mini->tab_save_env[i], 0, len(mini->tab_save_env[i]));
		if (strcmp(temp, "PATH") == 0)
		{
			free(temp);
			return (ft_strchr(mini->tab_save_env[i], '='));
		}
		free(temp);
		i++;
	}
	if (mini->tab_save_exp && mini->tab_save_exp[0] != NULL)
		return (utils_path_if_exi(mini));
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
		temp[i] = ft_strjoin(temp[i], "/");
		str = ft_strjoin(temp[i], lst->val[0]);
		free(temp[i]);
		if (access(str, F_OK) == 0)
		{
			free(str);
			execve(str, &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		free(str);
		i++;
	}
}
