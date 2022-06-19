/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:57:49 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 18:13:41 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../header/utiles_functions.h"

void	exec_first_cmd_in_her(t_list *list, t_shell *mini, int fd_out, int num)
{
	int	fd_in;
	int	fd;
	int	out;

	out = open_all_files(list, 2);
	fd_in = fd_i(list);
	close(fd);
	fd = open("/tmp/test", O_RDWR, 0644);
	norme_first_cmd(&list, mini);
	if (fork() == 0)
	{
		if (out == 1 && num == 1)
			ft_nor(mini, fd, fd_out);
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

char	**save_dele(t_list *list)
{
	int		i;
	char	**tab;

	tab = malloc(sizeof(char *) * 2);
	tab[1] = 0;
	tab[0] = ft_strdup(list->val[1]);
	i = 1;
	list = list->next;
	while (list && list->v_type[0] == 3)
	{
		tab = ft_realloc_char(tab);
		tab[i] = list->val[1];
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	norme_first_cmd(t_list **list, t_shell *mini)
{
	char	**sec_tab;
	int		io;
	int		lp;

	sec_tab = save_cmd(*list);
	io = 0;
	lp = 1;
	if (sec_tab[0])
	{
		while ((*list)->val[lp])
			lp++;
		while (sec_tab[io])
		{
			(*list)->val = ft_realloc_char((*list)->val);
			(*list)->val[lp] = sec_tab[io];
			io++;
			lp++;
		}
		(*list)->val[lp] = NULL;
		(*list)->v_type[0] = 1;
		(*list)->v_type[1] = 2;
	}
	ft_exit_status(mini, *list);
}

char	**save_cmd(t_list *list)
{
	int		i;
	t_list	*head;
	char	**tab;
	int		k;

	k = 2;
	i = ft_index(list);
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 3 || list->v_type[0] == 6
			|| list->v_type[0] == 8)
		{
			while (list->val[k])
			{
				tab[i++] = list->val[k];
				k++;
			}
			k = 2;
		}
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	norm_exec_her(t_shell *mini, t_list **list)
{
	char	**sec_tab;
	int		io;

	io = 0;
	sec_tab = save_cmd(*list);
	if (sec_tab[1])
	{
		while ((*list)->val[io])
		{
			(*list)->val = ft_realloc_char((*list)->val);
			(*list)->val[io] = sec_tab[io];
			io++;
		}
		(*list)->v_type[0] = 1;
		(*list)->v_type[1] = 2;
	}
	else if (sec_tab[0])
	{
		(*list)->val[0] = sec_tab[0];
		(*list)->val[1] = NULL;
		(*list)->v_type[0] = 1;
		(*list)->v_type[1] = 2;
	}
}
