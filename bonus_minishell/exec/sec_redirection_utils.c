/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_redirection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:37:09 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 02:41:32 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	norrrr(int fd, int in, int tem_fd)
{
	if (in != 0)
		dup2(in, 0);
	if (fd != 1)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(tem_fd, 0);
}

void	ft_redirection(t_shell *mini, t_list *lst, int a, int tem_fd)
{
	int		fd;
	int		in;

	(void)a;
	fd = open_all_files(lst, 0);
	in = fd_i(lst);
	utils_red(&lst);
	ft_exit_status(mini, lst);
	if (fd != -1)
	{
		g_id.id = fork();
		if (g_id.id == 0 && lst->v_type[0] == 1)
		{
			norrrr(fd, in, tem_fd);
			ft_check_built(mini, lst, fd);
			exit(0);
		}
		else if (g_id.id == 0)
			exit(0);
		close(fd);
		wait(NULL);
	}
}

int	utils_redin(t_list *lst)
{
	int	fd_in;

	while (lst && lst->v_type[0] == 8)
	{
		fd_in = open(lst->val[1], O_RDONLY, 0444);
		if (fd_in < 0)
		{
			fd_in = 0;
			break ;
		}
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (fd_in);
}

void	change_in(t_list **lst, t_shell *mini)
{
	int		i;

	i = 0;
	if (mini->tab_of_norm[i])
	{
		while ((*lst)->val[i])
			free((*lst)->val[i++]);
		free((*lst)->val);
		(*lst)->val = malloc(sizeof(char *) * (size_vl(mini->tab_of_norm) + 1));
		i = 0;
		while (mini->tab_of_norm[i])
		{
			(*lst)->val[i] = strdup(mini->tab_of_norm[i]);
			free(mini->tab_of_norm[i]);
			i++;
		}
		(*lst)->val[i] = NULL;
		(*lst)->v_type[0] = 1;
		(*lst)->v_type[1] = 2;
	}
	free(mini->tab_of_norm);
}

int	utils_re(t_list *lst, int fd_in, int k)
{
	while (lst && lst->v_type[0] == 8)
	{
		fd_in = open(lst->val[1], O_RDONLY, 0444);
		k = 2;
		if (fd_in < 0)
		{
			fd_in = 0;
			perror(NULL);
			break ;
		}
		lst = lst->next;
	}
	return (fd_in);
}
