/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:08:26 by otmallah          #+#    #+#             */
/*   Updated: 2022/03/18 21:08:27 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print2(char **tab, t_idx *idx)
{
	int i;
	int a;

	i = 0;
	a = idx->a;
	while(a >= 0)
	{
		printf("%s\n" , tab[i]);
		i++;
		a--;
	}
}

void	add_to_temp(t_mini *index, t_idx *id)
{
	int i;
	int j;
	char **temp;

	i = id->a;
	j = 0;
	temp = (char **)malloc(sizeof(char *) * id->b - 1);
	while (i >= 0)
	{
		temp[j] = index->env_tab[j];
		j++;
		i--;
	}
	free(index->env_tab);
	index->env_tab = (char **)malloc(sizeof(char *) * id->b);
	i = id->a;
	j = 0;
	while (i >= 0)
	{
		index->env_tab[j] = temp[j];
		j++;
		i--;
	}
	free(temp);
}

void    ft_env(t_mini *index, t_idx *id)
{
	int i;
	char	**tab;
	char **temp;

	i = 0;
	while (index->string[i])
	{
		printf("%s\n", index->string[i]);
		i++;
	}
	if (index->finde != NULL)
	{
		id->b++;
		if (!index->env_tab)
		{
			index->env_tab = (char **)malloc(sizeof(char *) * id->b);
			index->env_tab[id->a] = index->finde;
		}
		else
		{
			add_to_temp(index, id);
			if (index->finde != index->env_tab[id->a])
			{
				id->a++;
				index->env_tab[id->a] = index->finde;
			}
		}
		ft_print2(index->env_tab, id);
	}
}
