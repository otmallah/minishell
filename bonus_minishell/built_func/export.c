/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 14:32:33 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/25 22:27:07 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

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

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	utils_norm(t_shell *index, char **temp, int i, char *str)
{
	char	**sec_temp;

	sec_temp = ft_split(str, '=');
	if (ft_strcmp(temp[0], sec_temp[0]) == 0)
	{
		index->tab_save_env[i] = ft_strdup(str);
		ft_free(temp);
		ft_free(sec_temp);
		return (2);
	}
	ft_free(temp);
	ft_free(sec_temp);
	return (0);
}

int	norme2(t_shell *index, char *str, char **temp, char **sec_temp)
{
	int		i;

	i = 0;
	(void)sec_temp;
	while (index->tab_save_env[i])
	{
		temp = ft_split(index->tab_save_env[i], '=');
		if (len(str) == 0)
		{
			if (ft_strcmp(temp[0], str) == 0)
			{
				ft_free(temp);
				return (1);
			}
			ft_free(temp);
		}
		else
		{
			if (utils_norm(index, temp, i, str) == 2)
				return (2);
		}
		i++;
	}
	return (0);
}
