/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:39:02 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/25 22:18:25 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"
#include "../header/minishell.h"

int	ft_free_token_and_string(t_token *token, char *str, int n)
{
	if (!token->val && n == 0)
	{
		free(token);
		free(str);
		return (1);
	}
	if (token && token->val && n == 1)
	{
		free(token->val);
		free(token);
	}
	return (0);
}

void	ft_free_list(t_list *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->val[i])
			free(lst->val[i++]);
		free(lst->val);
		free(lst->v_type);
		if (lst->prev)
			free(lst->prev);
		if (!lst->next)
			free(lst);
			lst = lst->next;
	}
}

t_token	*ft_free_string(char *str, t_token *token)
{
	if (str)
		free(str);
	return (token);
}

void	ft_exit_prg(void)
{
	printf("exit\n");
	exit(0);
}
