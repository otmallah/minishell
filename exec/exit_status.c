/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:43:14 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 20:54:57 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_check_cmd2(t_shell *mini, t_list *lst);
char	*check_path_if_exi2(t_shell *mini);
void	normi(char **temp, t_shell *mini, t_list *lst);

void	ft_exit_status(t_shell *mini, t_list *lst)
{
	char	**temp;
	char	*str;
	int		i;

	i = 0;
	if (lst->val[0][0] == '.' || lst->val[0][0] == '/')
		ft_check_cmd2(mini, lst);
	else if (check_path_if_exi2(mini) != NULL)
	{
		str = check_path_if_exi(mini);
		if (str != NULL)
		{
			if (find(str) == 1)
				temp = ft_split(str, ':');
			else
			{
				temp = (char **)malloc(sizeof(char *) * 2);
				temp[i] = str;
				temp[i + 1] = NULL;
			}
			normi(temp, mini, lst);
		}
	}
	else
		g_status_exec = 127;
}

void	ft_check_cmd2(t_shell *mini, t_list *lst)
{
	DIR	*dp;

	dp = opendir(lst->val[0]);
	if ((int)dp == 512)
		g_status_exec = 126;
	if (lst->val[0][0] == '.')
	{
		if (access(lst->val[0], F_OK | X_OK) == 0)
			g_status_exec = 0;
		else
			g_status_exec = 127;
	}
	else if (lst->val[0][0] == '/')
	{
		if (access(lst->val[0], F_OK) == 0)
			g_status_exec = 0;
		else
			g_status_exec = 127;
	}
}	

void	normi(char **temp, t_shell *mini, t_list *lst)
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
			g_status_exec = 0;
			i = -1;
			break ;
		}
		free(str);
		i++;
	}
	free(temp);
	if (i != -1 && ft_strcmp(lst->val[0], "exit") != 0)
		g_status_exec = 127;
}

char	*check_path_if_exi2(t_shell *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_substr(mini->tab_save_env[i], 0, len(mini->tab_save_env[i]));
		if (strcmp(temp, "PATH") == 0)
			return (ft_strchr(mini->tab_save_env[i], '='));
		free(temp);
		i++;
	}
	if (mini->tab_save_exp && mini->tab_save_exp[0] != NULL)
	{
		i = 0;
		temp = ft_substr(mini->tab_save_exp[i], 0, len(mini->tab_save_exp[i]));
		if (strcmp(temp, "PATH") == 0)
			return (ft_strchr(mini->tab_save_exp[i], '='));
		free(temp);
		i++;
	}
	return (NULL);
}
