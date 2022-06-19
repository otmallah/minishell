/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:15:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 14:53:56 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	home(t_shell *mini)
{
	if (go_home(mini) == 0)
	{
		if (search_path_in_env(mini, 1) == 0)
			chdir("/Users/otmallah");
	}
	change_pwd(mini);
	mini->built++;
}

void	sec_home(t_shell *mini, char *path)
{
	path = ft_strjoin("/", ft_strchr(path, '/'));
	chdir(path);
	change_pwd(mini);
	mini->built++;
}

void	chdi(t_shell *mini, char *path)
{
	int	a;

	a = chdir(path);
	if (a != 0)
	{
		perror(NULL);
		g_status_exec = 1;
	}
	mini->built++;
	change_pwd(mini);
}

void	hh(t_shell *mini)
{
	if (search_path_in_env(mini, 1) == 0)
		perror(NULL);
	mini->built++;
}

void	ft_cd(char *path, t_shell *mini)
{
	int			a;
	char		buff[256];

	if (mini->built == 0)
		mini->save_pwd = strdup(getcwd(buff, sizeof(buff)));
	else
	{
		mini->save_old_pwd = strdup(mini->save_pwd);
		if (getcwd(buff, sizeof(buff)) != NULL)
			mini->save_pwd = strdup(getcwd(buff, sizeof(buff)));
	}
	if (!path)
		unset_home(mini);
	else if (strcmp(path, "~") == 0)
		home(mini);
	else if (strcmp(path, "-") == 0)
		oldpwd_not_set(mini);
	else if (path[0] == '~' && path[1] == '/')
		sec_home(mini, path);
	else if (path[0] == '$')
		hh(mini);
	else if (path)
		chdi(mini, path);
}
