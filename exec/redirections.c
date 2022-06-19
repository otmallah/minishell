/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:24:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 18:10:27 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/minishell.h"

void	normm3(t_shell *mini, t_list *list, int fd_in, int fd_out);
void	normee4(t_shell *mini, t_list *list);

void	change_in2(t_list **lst)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = cmd(*lst);
	if (tab[0])
	{
		if ((*lst)->v_type[0] == 1)
			i = 1;
		while ((*lst)->val[i])
			i++;
		while (tab[j])
		{
			(*lst)->val = ft_realloc_char((*lst)->val);
			(*lst)->val[i] = tab[j];
			i++;
			j++;
		}
		(*lst)->val[i] = malloc(sizeof(char *));
		(*lst)->val[i] = NULL;
		(*lst)->v_type[0] = 1;
		(*lst)->v_type[1] = 2;
	}
}

void	ft_redin(t_shell *mini, t_list *lst, int te_fd, int num)
{
	int		fd_in;
	int		fd_out;
	t_list	*head;
	int		k;

	head = lst;
	fd_out = 1;
	k = 2;
	if (lst->v_type[0] == 1)
	{
		lst = lst->next;
		fd_out = open_all_files(lst, 0);
		fd_in = utils_re(lst, fd_in, k);
		lst = head;
		change_in2(&lst);
		if (fd_in != 0)
		{
			if (fd_out != -1)
			{
				ft_exit_status(mini, lst);
				mini->id = fork();
				if (mini->id == 0)
				{
					dup2(fd_in, 0);
					if (fd_out != 1)
						dup2(fd_out, 1);
					else if (mini->counter == mini->num_ofall_cmd)
						dup2(1, 1);
					else if (num == 1 && fd_out == 1)
						dup2(te_fd, 1);
					ft_check_built(mini, lst, fd_out);
					exit(0);
				}
				close(fd_in);
				if (fd_out != 1)
					close(fd_out);
				wait(NULL);
				kill(9, mini->id);
			}
		}
	}
	else
		normee4(mini, lst);
}

void	normee4(t_shell *mini, t_list *list)
{
	int		fd_out;
	int		fd_in;
	t_list	*head;

	head = list;
	fd_out = open_all_files(list, 0);
	fd_in = utils_redin(list);
	list = head;
	mini->tab_of_norm = cmd(list);
	change_in(&list);
	if (fd_in != 0 && mini->tab_of_norm[0])
		normm3(mini, list, fd_in, fd_out);
}

void	normm3(t_shell *mini, t_list *list, int fd_in, int fd_out)
{
	if (fd_in != 0 && mini->tab_of_norm[0])
	{
		if (fd_out != -1)
		{
			mini->id = fork();
			if (mini->id == 0)
			{
				dup2(fd_in, 0);
				dup2(fd_out, 1);
				exec_cmd(mini, list);
				exit(0);
			}
			close(fd_in);
			if (fd_out != 1)
				close(fd_out);
			wait(NULL);
			kill(9, mini->id);
		}
	}
}
