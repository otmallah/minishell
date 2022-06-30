/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_utils_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:47:47 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/25 22:42:47 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	norme(t_shell *index);

void	ft_print_export(t_shell *index, char **str, int fd)
{
	int			i;
	static int	save_count;

	i = 1;
	norme(index);
	if (!str)
		ft_print(index, fd);
	if (str)
	{
		while (str[i])
		{
			if (invalide_identifier(str[i], fd) == 1)
				i++;
			else
			{
				if (str[i] != NULL)
					save_count = add_str_tab_exp(index, str[i]);
				i++;
			}
		}
	}
}

void	norme(t_shell *index)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (index->tab_save_env[i + 1] != NULL)
	{
		if (ft_strcmp(index->tab_save_env[i], index->tab_save_env[i + 1]) > 0)
		{
			temp = index->tab_save_env[i];
			index->tab_save_env[i] = index->tab_save_env[i + 1];
			index->tab_save_env[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

int	check_duplicate(t_shell *index, char *str)
{
	int		i;
	int		k;
	char	**temp;
	char	**sec_temp;

	i = 0;
	k = 0;
	temp = NULL;
	sec_temp = NULL;
	k = norme2(index, str, temp, sec_temp);
	if (k == 1 || k == 2)
		return (k);
	if (index->tab_save_exp)
	{
		i = 0;
		while (index->tab_save_exp[i])
		{
			if (duplicate_exp(index, index->tab_save_exp[i], str, i) != 0)
				return (3);
			i++;
		}
	}
	return (0);
}

void	oldpwd_not_set(t_shell *mini)
{
	if (mini->built == 0)
	{
		write(2, "cd: OLDPWD not set\n", 20);
		g_id.g_status_exec = 1;
	}
	else
	{
		printf("%s\n", mini->save_old_pwd);
		chdir(mini->save_old_pwd);
		change_pwd(mini);
	}
}

void	unset_home(t_shell *mini)
{
	if (go_home(mini) == 0)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		g_id.g_status_exec = 1;
	}
	else
	{	
		search_path_in_env(mini, 1);
		change_pwd(mini);
		mini->built++;
	}
}
