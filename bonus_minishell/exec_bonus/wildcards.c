/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:09:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 10:32:09 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	one_wild(t_wild *wild, int fd)
{
	wild->tab_wild[wild->size_j] = get_next_line(fd);
	wild->tab_wild[wild->size_j + 1] = NULL;
	while (wild->tab_wild[wild->size_j])
	{
		wild->size_j++;
		wild->tab_wild = ft_realloc_char(wild->tab_wild);
		wild->tab_wild[wild->size_j] = get_next_line(fd);
	}
}

void	import_all_arg(t_list **list, t_wild *wild, int fd)
{
	char	**tab;
	int		k;
	int		size;

	k = 1;
	close(fd);
	fd = open("/tmp/test1", O_RDWR, 0644);
	while (*list && (*list)->val[k])
	{
		tab = ft_split((*list)->val[k], '*');
		if (!tab[0])
			one_wild(wild, fd);
		else
			mult_wild(list, wild, tab, fd);
		close(fd);
		fd = open("/tmp/test1", O_RDWR, 0644);
		k++;
		if (size == wild->size_j)
			err_wild((*list)->val[k - 1]);
		ft_free(tab);
		size = wild->size_j;
	}
	wild->tab_wild[wild->size_j] = NULL;
	if (wild->size_j != 0)
		change(list, wild);
}

void	exec_wild(t_shell *mini, t_list **list)
{
	char	**temp;
	char	*str;

	str = check_path_if_exi(mini);
	if (str)
	{
		temp = ft_split(str, ':');
		if (temp[0])
			ft_execve(temp, mini, *list);
		ft_err((*list)->val[0]);
	}
	ft_err((*list)->val[0]);
}

void	utils_exec_wild(t_wild *wild, t_shell *mini, t_list **list, int fd_out)
{
	if (fork() == 0)
	{
		if (wild->out_file != 1)
			dup2(wild->out_file, 1);
		else if (fd_out != 0)
			dup2(fd_out, 1);
		if (wild->in_file != 0)
			dup2(wild->in_file, 0);
		exec_wild(mini, list);
	}
	wait(NULL);
	ft_free(wild->tab_wild);
}

void	ft_wildcards(t_list **list, t_shell *mini, int fd_out)
{
	char	**exec;
	int		fd;
	t_wild	wild;

	wild.size = 0;
	wild.size_j = 0;
	wild.tab_wild = (char **)malloc(sizeof(char *) * 2);
	exec = (char **)malloc(sizeof(char *) * 2);
	exec[0] = "ls";
	exec[1] = NULL;
	wild.out_file = open_all_files(*list, 2);
	wild.in_file = utils_redin(*list);
	unlink("/tmp/test1");
	fd = open("/tmp/test1", O_CREAT | O_RDWR, 0644);
	if (fork() == 0)
	{
		dup2(fd, 1);
		execve("/bin/ls", exec, mini->tab_save_env);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	import_all_arg(list, &wild, fd);
	utils_exec_wild(&wild, mini, list, fd_out);
	free(exec);
}
