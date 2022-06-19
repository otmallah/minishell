/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:32:33 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 20:59:18 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	finder(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	if (str[i] == '=')
		return (2);
	return (0);
}

int	checker(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47)
			|| (str[i] >= 58 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 94)
			|| (str[i] >= 123 && str[i] <= 126))
			return (1);
		i++;
	}
	return (0);
}

int	norme2(t_shell *index, char *str, char **temp, char **sec_temp)
{
	int		i;
	int		a;

	i = 0;
	while (index->tab_save_env[i])
	{
		temp = ft_split(index->tab_save_env[i], '=');
		a = len(str);
		if (a == 0)
		{
			if (ft_strcmp(temp[0], str) == 0)
				return (1);
		}
		else
		{
			sec_temp = ft_split(str, '=');
			if (ft_strcmp(temp[0], sec_temp[0]) == 0)
			{
				index->tab_save_env[i] = str;
				return (2);
			}
		}
		i++;
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
			index->tab_save_exp[count] = str;
			index->tab_save_exp[count + 1] = NULL;
		}
		else
			ft_realloc(index, str, count);
		count++;
	}
	return (count);
}

int	invalide_identifier(char *str, int fd)
{
	if (str[0] >= '0' && str[0] <= '9')
	{
		ft_putstr_fd("export: not an identifier: ", fd);
		ft_putendl_fd(str, fd);
		g_status_exec = 127;
		return (1);
	}
	else if (str[0] == '-')
	{
		ft_putstr_fd("export: invalid option: ", fd);
		ft_putendl_fd(str, fd);
		g_status_exec = 127;
		return (1);
	}
	else if (finder(str) == 1 || str[0] == '+'
		|| checker(str) == 1 || str[0] == '=' || str[0] == '\0')
	{
		ft_putstr_fd("export: not a 5valid identifier: ", fd);
		ft_putendl_fd(str, fd);
		g_status_exec = 127;
		return (1);
	}
	return (0);
}
