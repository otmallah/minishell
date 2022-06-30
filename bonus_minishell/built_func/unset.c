/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 03:56:14 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	norme3(t_shell *index, char **temp, char *str)
{
	int		i;
	int		j;
	char	**save;

	i = 0;
	j = 0;
	while (index->tab_save_exp[i])
	{
		if (len(index->tab_save_exp[i]) == 0)
		{
			save = (char **)malloc(sizeof(char *) + 1);
			save[0] = index->tab_save_exp[i];
			save[1] = NULL;
		}
		else
			save = ft_split(index->tab_save_exp[i], '=');
		if (ft_strcmp(save[0], str) != 0)
			temp[j++] = index->tab_save_exp[i++];
		else
			free(index->tab_save_exp[i++]);
		ft_free(save);
	}
	free(index->tab_save_exp);
	temp[j] = NULL;
}

void	unset_exp(t_shell *index, char *str)
{
	char		**temp;
	int			i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (tablen(index->tab_save_exp) + 1));
	norme3(index, temp, str);
	index->tab_save_exp = (char **)malloc(sizeof(char *) * (tablen(temp) + 1));
	i = 0;
	while (temp && temp[i])
	{
		index->tab_save_exp[i] = temp[i];
		i++;
	}
	index->tab_save_exp[i] = NULL;
	free(temp);
}

void	norme4(t_shell *index, char **temp, char *str, char **save)
{
	int			i;
	int			j;
	static int	n;

	i = 0;
	j = 0;
	while (index->tab_save_env && index->tab_save_env[i])
	{
		save = ft_split(index->tab_save_env[i], '=');
		if (ft_strcmp(save[0], str) != 0)
		{
			temp[j] = index->tab_save_env[i];
			j++;
			i++;
		}
		else
		{
			if (n > 0)
				free(index->tab_save_env[i]);
			i++;
		}
		ft_free(save);
	}
	ft_copy_tab_save_env(index, temp, n, j);
	n++;
}

void	ft_unset(t_shell *index, char **str, int fd)
{
	int		k;
	char	**save;
	char	**temp;

	k = 1;
	save = NULL;
	while (str[k])
	{
		if (finder(str[k]) == 2)
		{
			ft_putstr_fd("unset: not a valid identifier: ", fd);
			ft_putendl_fd(str[k], fd);
			k++;
			g_id.g_status_exec = 1;
		}
		else if (invalide_identifier(str[k], fd) == 1)
			k++;
		else
		{
			temp = malloc(sizeof(char *) * (tablen(index->tab_save_env) + 1));
			ft_13(index, str[k], save, temp);
			k++;
		}
	}
}
