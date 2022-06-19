/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:55:24 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 14:30:13 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ex(t_shell *mini, t_list *list, int *save, int fs);

int	check_her(t_list *list)
{
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4)
			return (1);
		list = list->next;
	}
	return (0);
}

int	num_of_cmd(t_list *list)
{
	int	count;
	int	is_her;

	count = 0;
	while (list)
	{
		is_her = 0;
		while (list && list->v_type[0] != 11)
			list = list->next;
		if (is_her == 0)
			count++;
		if (list)
			list = list->next;
	}
	return (count);
}

void	pipes(t_shell *mini, t_list *list)
{
	int		fd[2];
	t_list	*head;
	int		i;
	int		fs;

	fs = 0;
	mini->num_cmd = num_of_cmd(list);
	mini->num_ofall_cmd = mini->num_cmd;
	mini->save = malloc(sizeof(int) * mini->num_cmd);
	head = list;
	i = 0;
	while (i < mini->num_cmd && list)
		i = nomm1(&list, mini, fd, i);
	if (mini->cnt == 2)
	{
		list = head;
		ex(mini, list, mini->save, fs);
	}
	while (mini->fs-- >= 0)
		waitpid(mini->save[mini->fs], 0, 0);
	unlink("/tmp/test");
}

int	fin(t_list *list)
{
	if (list && list->next && (list->next->v_type[0] == 6
			|| list->next->v_type[0] == 8 || list->next->v_type[0] == 3
			|| list->next->v_type[0] == 4
			|| list->v_type[0] == 3) && list->next->next)
		return (1);
	return (0);
}

void	simple_cmd(t_shell *mini, t_list *list, int i, int *fd)
{
	mini->counter = i + 1;
	mini->id = fork();
	if (mini->id == 0)
	{
		if (i == 0)
			exec_first_cmd(list, mini, fd);
		else if (i == (mini->num_cmd - 1))
			exec_last_cmd(list, mini, mini->temp_fd, fd);
		else
			exec_sec_cmd(list, mini, mini->temp_fd, fd);
		exit(0);
	}
}
