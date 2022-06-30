/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:34:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/25 20:31:10 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	true_while(char **tab, int size);

int	fd_i(t_list *list)
{
	int	fd;

	fd = 0;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 8)
			fd = open(list->val[1], O_RDWR, 0644);
		list = list->next;
	}
	return (fd);
}

void	ft_norme(t_shell *mini, int fd, int fd_out, int fd_in)
{
	if (fd_in != 0)
		dup2(fd_in, 0);
	else
		dup2(fd, 0);
	if (mini->counter == mini->num_ofall_cmd)
		dup2(1, 1);
	else
		dup2(fd_out, 1);
}

void	exec_her(t_list *list, t_shell *mini, int num, int fd_out)
{
	int	fd_in;
	int	fd;
	int	out;

	out = open_all_files(list, 2);
	fd_in = fd_i(list);
	fd = open("/tmp/test", O_RDWR, 0644);
	norm_exec_her(mini, &list);
	if (fork() == 0)
	{
		if (out == 1 && num == 1)
			ft_norme(mini, fd, fd_out, fd_in);
		else
		{
			if (fd_in != 0)
				dup2(fd_in, 0);
			else
				dup2(fd, 0);
			dup2(out, 1);
		}
		ft_check_built(mini, list, 1);
		exit(0);
	}
	wait(NULL);
}

int	utils_true_while(void)
{
	int	fd;

	fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	return (fd);
}

void	heredoc(t_shell *mini, t_list *list, int num, int fd_out)
{
	int		out;
	char	**tab;
	int		size;

	if (list->v_type[0] != 1 && list->v_type[0] == 3)
		tab = save_dele(list);
	else
		tab = save_dele(list->next);
	size = size_tab(tab);
	true_while(tab, size);
	out = open_all_files(list, 2);
	if (list->v_type[0] == 1 && out != -1 && g_id.cheecker == 1)
		exec_first_cmd_in_her(list, mini, fd_out, num);
	else if (out != -1 && g_id.cheecker == 1)
		exec_her(list, mini, num, fd_out);
	if (out == -1)
		printf("No such file or directory\n");
	if (num != 1 || out != 1)
		unlink("/tmp/test");
}
