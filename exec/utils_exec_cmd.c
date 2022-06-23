/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:45:08 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 03:08:47 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	cmm(t_list *lst, t_shell *mini)
{
	int	wstatus;

	id = fork();
	if (id == 0)
		exec_cmd(mini, lst);
	else
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			g_status_exec = WEXITSTATUS(wstatus);
			if (g_status_exec == 1)
				g_status_exec = 127;
		}
	}
}

void	cmm_exit(t_list *lst, int fd)
{
	if (lst->val[1] != NULL && lst->v_type[1] != 0)
		ft_exit(lst->val, fd, 0);
	else
		ft_exit(NULL, fd, 0);
}

void	cmm_cd(t_list *lst, t_shell *mini)
{
	if (lst->val[1])
		ft_cd(lst->val[1], mini);
	else
		ft_cd(NULL, mini);
}

void	built_sec(t_shell *mini, t_list *lst, int fd)
{
	if (strcmp(lst->val[0], "export") == 0)
	{
		if (lst && size_vl(lst->val) > 1)
			ft_print_export(mini, lst->val, 1);
		else
			ft_print_export(mini, NULL, 1);
	}
	else if (strcmp(lst->val[0], "pwd") == 0)
		ft_pwd(fd);
	else if (strcmp(lst->val[0], "env") == 0)
		ft_env(mini, fd);
	else if (strcmp(lst->val[0], "exit") == 0)
		cmm_exit(lst, fd);
	else if (strcmp(lst->val[0], "unset") == 0)
	{
		if (lst && lst->val[1] != NULL)
			ft_unset(mini, lst->val, fd);
	}
	else if (strcmp(lst->val[0], "cd") == 0)
		cmm_cd(lst, mini);
	else if (ft_strcmp(lst->val[0], "echo") == 0)
		ft_echo(mini, lst->val, fd);
	else
		cmm(lst, mini);
}

char	*ft_getenv_utils(t_shell *m, char *str)
{
	char	*temp;
	int		j;

	j = 0;
	while (m->tab_save_exp[j])
	{
		temp = ft_substr(m->tab_save_exp[j], 0, len(m->tab_save_exp[j]));
		if (strcmp(temp, str) == 0)
		{
			free(temp);
			return (ft_strchr(m->tab_save_exp[j], '='));
		}
		free(temp);
		j++;
	}
	return (NULL);
}
