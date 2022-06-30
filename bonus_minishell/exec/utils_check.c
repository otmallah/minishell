/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:45:43 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/27 00:45:56 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ft_check_cmd_if_exists(t_shell *mini, t_list *lst, DIR *dp)
{
	if (lst->val[0][0] == '/')
	{
		dp = opendir(lst->val[0]);
		if ((int)dp != 0)
		{
			printf("minishell: ./exec: is a directory\n");
			exit(126);
		}
		else if (access(lst->val[0], F_OK) == 0)
		{
			execve(lst->val[0], &lst->val[0], mini->tab_save_env);
			exit(0);
		}
		else
			ft_err(lst->val[0]);
	}
}

int	ft_free_and_dup_val(t_list **list, char **sec_tab, int io)
{
	free((*list)->val[io]);
	(*list)->val[io] = ft_strdup(sec_tab[io]);
	io++;
	return (io);
}

int	ft_free_lst_val(t_list **lst, int ij)
{
	while ((*lst)->val[ij])
		free((*lst)->val[ij++]);
	free((*lst)->val);
	return (ij);
}

int	ft_check_cmd_out(t_list *list)
{
	if (((ft_strcmp(list->val[0], "cat") == 0 && !list->val[1]
				&& list->val[1][0] != '-')
		|| (ft_strcmp(list->val[0], "wc") == 0 && !list->val[1]
			&& list->val[1][0] != '-')
			|| (ft_strcmp(list->val[0], "grep") == 0 && !list->val[1]
			&& list->val[1][0] != '-')
			|| (ft_strcmp(list->val[0], "more") == 0)) && !list->val[1]
			&& list->val[1][0] != '-')
		return (1);
	return (0);
}
