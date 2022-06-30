/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_string_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 05:39:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 05:44:43 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	finde_her(t_list *lis)
{
	while (lis)
	{
		if (lis->v_type[0] == 11)
			return (1);
		lis = lis->next;
	}
	return (0);
}

int	ft_findwild(t_list *list)
{
	while (list && list->v_type[0] != 11)
	{
		if (list->val[1])
		{
			if (list->v_type[1] == 15)
				return (1);
		}
		if (list->v_type[0] == 13)
			return (2);
		if (list->v_type[0] == 12)
			return (3);
		list = list->next;
	}
	return (0);
}

int	find_both_and_or(t_list *list)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 13)
			a = 1;
		if (list->v_type[0] == 12)
			b = 1;
		list = list->next;
	}
	if (a + b == 2)
		return (1);
	return (0);
}

int	finder_red(t_list *list)
{
	while (list)
	{
		if (list && (list->v_type[0] == 6 || list->v_type[0] == 4))
			return (2);
		else if (list && list->v_type[0] == 8)
			return (3);
		else if (list && list->v_type[0] == 3)
			return (4);
		list = list->next;
	}
	return (0);
}

void	ft_mini_second(t_shell *mini, t_list *lst)
{
	if (finder_red(lst) == 2)
		ft_redirection(mini, lst, 0, 1);
	else if (finder_red(lst) == 4)
		heredoc(mini, lst, 0, 1);
	else if (finder_red(lst) == 3)
		ft_redin(mini, lst, 1, 0);
	else
	{
		ft_exit_status(mini, lst);
		ft_check_built(mini, lst, 1);
	}
}
