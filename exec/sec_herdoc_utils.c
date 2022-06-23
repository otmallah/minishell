/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_herdoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:12:10 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/21 23:23:09 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	ft_index(t_list *list)
{
	int	k;
	int	i;

	k = 2;
	i = 0;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 3 || list->v_type[0] == 6)
		{
			while (list->val[k])
			{
				k++;
				i++;
			}
			k = 2;
		}
		list = list->next;
	}
	return (i);
}

void	ft_nor(t_shell *mini, int fd, int fd_out)
{
	dup2(fd, 0);
	if (mini->counter == mini->num_ofall_cmd)
		dup2(1, 1);
	else
		dup2(fd_out, 1);
}

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ex(t_shell *mini, t_list *list, int *save, int fs)
{
	int	fd;

	fd = open("/tmp/test", O_CREAT | O_RDWR);
	mini->id = fork();
	id = mini->id;
	if (mini->id == 0)
	{
		if (list->next && (list->next->v_type[0] == 6
				|| list->next->v_type[0] == 4))
			ft_redirection(mini, list, 1, 1);
		else if ((list->next && list->next->v_type[0] == 8)
			|| list->v_type[0] == 8)
			ft_redin(mini, list, fd, 1);
		else
		{
			dup2(fd, 1);
			exec_cmd(mini, list);
		}
		wait(NULL);
		exit(0);
	}
}
