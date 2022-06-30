/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:43:14 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 09:55:00 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ft_check_cmd2(t_shell *mini, t_list *lst);
char	*check_path_if_exi2(t_shell *mini);
void	normi(char **temp, t_shell *mini, t_list *lst);

void	ft_exit_status(t_shell *mini, t_list *lst)
{
	char	**temp;
	char	*str;
	int		i;

	i = 0;
	str = check_path_if_exi2(mini);
	if (lst->val[0][0] == '.' || lst->val[0][0] == '/')
		ft_check_cmd2(mini, lst);
	else if (str != NULL)
	{	
		temp = ft_split(str, ':');
		normi(temp, mini, lst);
	}
	else
		g_id.g_status_exec = 127;
}

void	ft_check_cmd2(t_shell *mini, t_list *lst)
{
	DIR		*dp;

	(void)mini;
	dp = opendir(lst->val[0]);
	if ((int)dp != 0)
	{
		free(dp->__dd_buf);
		free(dp);
		g_id.g_status_exec = 126;
	}
	else if (lst->val[0][0] == '.')
	{
		if (access(lst->val[0], F_OK | X_OK) == 0)
			g_id.g_status_exec = 0;
		else
			g_id.g_status_exec = 127;
	}
	else if (lst->val[0][0] == '/')
	{
		if (access(lst->val[0], F_OK) == 0)
			g_id.g_status_exec = 0;
		else
			g_id.g_status_exec = 127;
	}
}	

void	normi(char **temp, t_shell *mini, t_list *lst)
{
	int		i;
	char	*str;

	i = 0;
	(void)mini;
	while (temp[i])
	{
		temp[i] = ft_h_strjoin(temp[i], "/");
		str = ft_h_strjoin(temp[i], lst->val[0]);
		if (access(str, F_OK) == 0)
		{
			i++;
			while (temp[i])
				free(temp[i++]);
			free(str);
			g_id.g_status_exec = 0;
			i = -1;
			break ;
		}
		free(str);
		i++;
	}
	free(temp);
	add_name2(i, lst->val[0]);
}

char	*utils_check_path_if_exi2(t_shell *mini)
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

char	*check_path_if_exi2(t_shell *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_substr(mini->tab_save_env[i], 0, len(mini->tab_save_env[i]));
		if (ft_strcmp(temp, "PATH") == 0)
		{
			free(temp);
			return (ft_strchr(mini->tab_save_env[i], '='));
		}
		free(temp);
		i++;
	}
	if (mini->tab_save_exp && mini->tab_save_exp[0] != NULL)
		return (utils_check_path_if_exi2(mini));
	return (NULL);
}
