/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:07:33 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 04:44:36 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	size_vl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_check_built(t_shell *mini, t_list *lst, int fd)
{
	if (lst->val && lst->v_type[0] == 1)
		built_sec(mini, lst, fd);
}

int	find(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

void	exec_cmd(t_shell *mini, t_list *lst)
{
	char	**temp;
	char	*str;

	str = check_path_if_exi(mini);
	if (lst->val[0][0] == '.' || lst->val[0][0] == '/')
		ft_check_cmd(mini, lst);
	else if (str != NULL)
	{
		if (str != NULL)
		{
			temp = ft_split(str, ':');
			if (temp[0])
				ft_execve(temp, mini, lst);
			ft_err(lst->val[0]);
		}
	}
	else
		ft_err(lst->val[0]);
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
