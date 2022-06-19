/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:34:38 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 14:46:04 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/utiles_functions.h"

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

void	ft_norme(t_shell *mini, int fd, int fd_out)
{
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
	ft_exit_status(mini, list);
	if (fork() == 0)
	{
		if (out == 1 && num == 1)
			ft_norme(mini, fd, fd_out);
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

void	true_while(t_shell *mini, char **tab, int size)
{
	char	*find;
	int		fd;
	int		i;

	i = 0;
	fd = open("/tmp/test", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		find = readline("> ");
		if (find == NULL)
			break ;
		if (strcmp(find, tab[i]) == 0 && tab[i])
		{
			size--;
			i++;
			if (size == 0)
				break ;
			else
				fd = open("/tmp/test", O_RDWR | O_TRUNC, 0644);
		}
		if (size != 0)
			ft_putendl_fd(find, fd);
	}
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
	true_while(mini, tab, size);
	out = open_all_files(list, 2);
	if (list->v_type[0] == 1 && out != -1)
		exec_first_cmd_in_her(list, mini, fd_out, num);
	else if (out != -1)
		exec_her(list, mini, num, fd_out);
	if (out == -1)
		printf("No such file or directory\n");
	if (num != 1 || out != 1)
		unlink("/tmp/test");
}
