/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:13:36 by otmallah          #+#    #+#             */
/*   Updated: 2022/03/18 18:13:36 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int tablen(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

int	findlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return i;
		i++;
	}
	return 0;
}

void	add_to_f(t_mini *index, t_idx *id, char *str)
{
	int i;
	int j;
	int a;
	char **temp;
	char *temp2;

	i = id->b;
	j = 0;
	a = 0;
	temp = (char **)malloc(sizeof(char *) * id->b);
	while (i > 0)
	{
		temp2 = ft_substr(index->string[j], 0, findlen(index->string[j]));
		if (ft_strcmp(temp2, str) == 0)
		{
			j++;
		}
		temp[a] = index->string[j];
		//printf("temp = %s\n", temp[a]);
		j++;
		i--;
		a++;
	}
	//free()
	index->string = (char **)malloc(sizeof(char *) * (id->b));
	i = id->b;
	j = 0;
	while (i > 0)
	{
		index->string[j] = temp[j];
		j++;
		i--;
	}
	//printf("st = %s\n", index->string[i]);
	index->string[i] = NULL;
}

//void	//same_in_expor

void	ft_unset(t_mini *index, t_idx *id, char *str)
{
	int i;
	char *temp;

	i = 0;
	while (index->tab_unset[i])
	{
		temp = ft_substr(index->tab_unset[i], 0, findlen(index->tab_unset[i]));
		if (ft_strcmp(temp, str) == 0)
		{
			id->b = tablen(index->tab_unset) - id->poor;
			id->poor++;
			add_to_f(index, id, str);
			//same_in_expor(index, id);
		}
		i++;
	}
	//if (index->env_tab)
	//{
	//	i = 0;
	//	while (index->env_tab[i])
	//	{
	//		temp = ft_substr(index->env_tab[i], 0, findlen(index->env_tab[i]));
	//		if (ft_strcmp(temp, str) == 0)
	//		{
	//			
	//		}
	//	}
	//}
	//printf("%s\n", index->tab_unset[i]);
}