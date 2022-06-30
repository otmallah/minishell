/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_second.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:25:59 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/19 19:26:02 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	add_node_in_back(t_list *new, t_list *lst)
{
	while (lst->next)
	{
		if (lst->next)
			lst->next->prev = lst;
		lst = lst->next;
	}
	lst->next = new;
	lst->next->prev = lst;
}

t_list	*add_node_in_lst(char *str, int v_type, t_list *lst)
{
	t_list	*new;
	t_list	*head;

	head = lst;
	if (v_type == t_args)
		v_type = 1;
	new = malloc(sizeof(t_list));
	new->val = malloc (sizeof(char *) * 2);
	new->v_type = malloc(sizeof(int));
	new->val[0] = str;
	new->val[1] = NULL;
	new->v_type[0] = v_type;
	new->next = NULL;
	new->prev = NULL;
	if (lst)
		add_node_in_back(new, lst);
	else
		head = new;
	return (head);
}
