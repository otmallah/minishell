/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:04 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/25 22:47:40 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ft_realloc(t_shell *index, char *str, int save)
{
	char	**temp;
	int		a;

	temp = (char **)malloc(sizeof(char *) * (save + 1));
	a = 0;
	while (index->tab_save_exp[a])
	{
		temp[a] = index->tab_save_exp[a];
		a++;
	}
	temp[a] = NULL;
	index->tab_save_exp = (char **)malloc(sizeof(char *) * (save + 2));
	a = 0;
	while (temp[a])
	{
		index->tab_save_exp[a] = temp[a];
		a++;
	}
	index->tab_save_exp[a] = ft_strdup(str);
	index->tab_save_exp[a + 1] = NULL;
}

void	ft_print(t_shell *index, int fd)
{
	int	i;

	i = 0;
	while (index->tab_save_env[i])
	{
		ft_putstr_fd("decalre -x ", fd);
		ft_putendl_fd(index->tab_save_env[i], fd);
		i++;
	}
	if (index->tab_save_exp && index->tab_save_exp[0])
	{
		i = 0;
		while (index->tab_save_exp[i])
		{
			ft_putstr_fd("decalre -x ", fd);
			ft_putendl_fd(index->tab_save_exp[i], fd);
			i++;
		}
	}
	g_id.g_status_exec = 0;
}

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	duplicate_exp(t_shell *index, char *string, char *add_str, int i)
{
	int		checker;
	char	**temp;

	checker = len(add_str);
	if (len(string) != 0 && checker != 0)
		return (no(index, add_str, string, i));
	else if (len(string) != 0 && checker == 0)
	{
		temp = ft_split(string, '=');
		if (ft_strcmp(temp[0], add_str) == 0)
		{
			ft_free(temp);
			return (4);
		}
		ft_free(temp);
	}
	else if (len(string) == 0 && checker != 0)
		return (no1(index, add_str, string, i));
	else
	{
		if (ft_strcmp(add_str, string) == 0)
			return (6);
	}
	return (0);
}

int	find_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
