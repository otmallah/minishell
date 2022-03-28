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

int tablen1(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return i;
}

void    ft_env(t_mini *index, t_idx *id)
{
	int i = 0;
	int a = 0;
	int j = 0;
	char	**tab;
	char **temp;

	puts("hana");
	index->tab_unset = index->string;
	printf("%s \n", index->tab_unset[i]);
	while (index->tab_unset[i])
	{
		printf("%s\n", index->tab_unset[i]);
		i++;
	}
	//puts("*-*-**-*-*-*-*-*-*-*-*-*-*-*-*");
	if (index->env_tab)
	{
		ft_print2(index->env_tab, id);
	}
}

//void	ft_print_alllist(t_list *list)
//{
//	while (list != NULL)
//	{
//		printf("%s\n", list->content);
//		list = list->next;
//	}
//}
//
//void    ft_env(t_mini *index, t_list *list)
//{
//    int i;
//
//    i = 0;
//    list = ft_lstnew(index->tab_exp[i]);
//    i += 1;
//    while (index->tab_exp[i])
//    {
//        ft_lstadd_back(&list, ft_lstnew(index->tab_exp[i]));
//        i++;
//    }
//	ft_print_alllist(list);
//}
