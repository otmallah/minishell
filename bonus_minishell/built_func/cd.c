/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:15:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 09:36:19 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	chdi(t_shell *mini, char *path);
void	old(t_shell *mini, int a);

char	**go_home2(t_shell *mini)
{
	int		i;
	int		j;
	char	**temp;

	j = 0;
	i = 0;
	while (mini->tab_save_env[i])
	{
		temp = ft_split(mini->tab_save_env[i], '=');
		if (ft_strcmp(temp[0], "HOME") == 0)
			return (temp);
		ft_free(temp);
		j = 0;
		i++;
	}
	return (0);
}

void	home(t_shell *mini)
{
	char	**str;
	int		i;

	i = 0;
	str = go_home2(mini);
	if (str[1] != NULL)
	{
		chdir(str[1]);
		ft_free(str);
	}
	change_pwd(mini);
	mini->built++;
}

void	sec_home(t_shell *mini, char *path)
{
	char	*temp;
	char	**sec_temp;
	char	*tab;
	int		a;

	sec_temp = go_home2(mini);
	temp = ft_strchr(path, '/');
	tab = ft_strjoin("/", temp);
	path = ft_strjoin(sec_temp[1], tab);
	a = chdir(path);
	if (a < 0)
		perror(NULL);
	free(tab);
	free(path);
	ft_free(sec_temp);
	change_pwd(mini);
	mini->built++;
}

void	hh(t_shell *mini)
{
	if (search_path_in_env(mini, 1) == 0)
		perror(NULL);
	mini->built++;
}

void	ft_cd(char *path, t_shell *mini)
{
	static int			a;
	char				buff[256];
	char				*temp;

	if (mini->built == 0)
		mini->save_pwd = ft_strdup(getcwd(buff, sizeof(buff)));
	if (mini->save_pwd)
	{
		temp = getcwd(buff, sizeof(buff));
		if (temp && ft_strcmp(mini->save_pwd, temp) != 0)
			old(mini, a);
	}
	if (path == NULL)
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
	a++;
}
