/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:43:32 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/22 18:53:38 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	exec_first_cmd(t_list *list, t_shell *mini, int *fd)
{
	close(fd[0]);
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6
		|| list->v_type[0] == 4 || (list->next && list->next->v_type[0] == 4))
		ft_redirection(mini, list, 1, fd[1]);
	else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
		ft_redin(mini, list, fd[1], 1);
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(fd[1], 1);
		ft_check_built(mini, list, 1);
	}
}

void	exec_last_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd)
{
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6
		|| list->v_type[0] == 4 || (list->next && list->next->v_type[0] == 4))
	{
		dup2(temp_fd, 0);
		ft_redirection(mini, list, 1, fd[1]);
	}
	else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
	{
		close(temp_fd);
		ft_redin(mini, list, fd[1], 1);
	}
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(temp_fd, 0);
		ft_check_built(mini, list, 1);
	}
}

void	exec_sec_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd)
{
	close(fd[0]);
	if ((list->next && list->next->v_type[0] == 6) || list->v_type[0] == 6
		|| list->v_type[0] == 4 || (list->next && list->next->v_type[0] == 4))
	{
		dup2(temp_fd, 0);
		ft_redirection(mini, list, 1, fd[1]);
	}
	else if ((list->next && list->next->v_type[0] == 8) || list->v_type[0] == 8)
		ft_redin(mini, list, fd[1], 1);
	else if (ft_strcmp(list->val[0], "exit") != 0 && list->v_type[0] == 1)
	{
		dup2(fd[1], 1);
		dup2(temp_fd, 0);
		ft_check_built(mini, list, 1);
	}
}

void	normm(t_list *list, t_shell *mini, int *fd, int i)
{
	int	k;

	k = i;
	ft_exit_status(mini, list);
	if (pipe(fd) < 0)
		perror("pipe");
	if (list && ft_strcmp(list->val[0], "exit") == 0 && list->val[1])
		ft_exit(list->val, 1, 1);
	else if (list && list->next && list->next->v_type[0] != 3 && i == 0
		&& ft_check_cmd_out(list))
		mini->cnt = 2;
	else if (ft_findwild(list) == 1)
	{
		ft_wildcards(&list, mini, fd[1]);
		wait(NULL);
	}
	else if ((list->next && list->next->v_type[0] == 3) || list->v_type[0] == 3)
	{
		mini->counter = i + 1;
		heredoc(mini, list, 1, fd[1]);
		while (k--)
			wait(NULL);
	}
	else
		simple_cmd(mini, list, i, fd);
}

int	nomm1(t_list **list, t_shell *mini, int *fd, int i)
{
	normm(*list, mini, fd, i);
	mini->save[mini->fs] = mini->id;
	mini->fs++;
	mini->temp_fd = dup(fd[0]);
	close(fd[0]);
	close(fd[1]);
	i++;
	if (fin(*list) == 1)
	{
		while (*list && (*list)->next && (*list)->v_type[0] != 11)
			*list = (*list)->next;
		*list = (*list)->next;
	}
	else if ((*list)->next)
	{
		mini->counter++;
		*list = (*list)->next->next;
	}
	return (i);
}
