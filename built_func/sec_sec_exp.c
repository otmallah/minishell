/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_sec_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:56:19 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/25 22:39:50 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

int	checker(char *str);
int	ut2(t_shell *mini, int a);

int	invalide_identifier(char *str, int fd)
{
	if (str[0] >= '0' && str[0] <= '9')
	{
		ft_putstr_fd("export: not an identifier: ", fd);
		ft_putendl_fd(str, fd);
		g_id.g_status_exec = 127;
		return (1);
	}
	else if (str[0] == '-')
	{
		ft_putstr_fd("export: invalid option: ", fd);
		ft_putendl_fd(str, fd);
		g_id.g_status_exec = 127;
		return (1);
	}
	else if (finder(str) == 1 || str[0] == '+'
		|| checker(str) == 1 || str[0] == '=' || str[0] == '\0')
	{
		ft_putstr_fd("export: not a 5valid identifier: ", fd);
		ft_putendl_fd(str, fd);
		g_id.g_status_exec = 127;
		return (1);
	}
	return (0);
}

int	add_str_tab_exp(t_shell *index, char *str)
{
	static int	count;
	int			save;

	save = check_duplicate(index, str);
	if (save == 0)
	{
		if (count == 0)
		{
			index->tab_save_exp = (char **)malloc(sizeof(char *) * 2);
			index->tab_save_exp[0] = ft_strdup(str);
			index->tab_save_exp[1] = NULL;
		}
		else
		{
			index->tab_save_exp = ft_realloc_char(index->tab_save_exp);
			index->tab_save_exp[count] = ft_strdup(str);
		}
		count++;
	}
	return (count);
}

int	utils_search(t_shell *mini, int a)
{
	int	k;

	k = ut2(mini, a);
	if (k == 1)
		return (1);
	return (1);
}

int	search_path_in_env(t_shell *mini, int a)
{
	int		i;
	char	**str;
	int		k;

	i = 0;
	while (mini->tab_save_env[i])
	{
		str = ft_split(mini->tab_save_env[i], '=');
		if (ft_strcmp(str[0], "HOME") == 0)
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
	k = utils_search(mini, a);
	if (k == 1)
		return (k);
	return (0);
}

void	chdi(t_shell *mini, char *path)
{
	int	a;

	a = chdir(path);
	if (a != 0)
	{
		perror(NULL);
		g_id.g_status_exec = 1;
	}
	mini->built++;
	change_pwd(mini);
}
