/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:07:33 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 19:11:15 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	size_vl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	built_sec(t_shell *mini, t_list *list);

void	ft_check_built(t_shell *mini, t_list *lst, int fd)
{
	int	wstatus;

	if (lst->val && lst->v_type[0] == 1)
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
		{
			if (lst->val[1] != NULL && lst->v_type[1] != 0)
				ft_exit(lst->val, fd, 0);
			else
				ft_exit(NULL, fd, 0);
		}
		else if (strcmp(lst->val[0], "unset") == 0)
		{
			if (lst && lst->val[1] != NULL)
				ft_unset(mini, lst->val, fd);
		}
		else if (strcmp(lst->val[0], "cd") == 0)
		{
			if (lst->val[1] != NULL)
				ft_cd(lst->val[1], mini);
			else
				ft_cd(NULL, mini);
		}
		else if (ft_strcmp(lst->val[0], "echo") == 0)
			ft_echo(mini, lst->val, fd);
		else
		{
			id = fork();
			printf("pid = %d\n", id);
			if (id == 0)
			{
				exec_cmd(mini, lst);
			}
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
	}
}

int	find(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

void	exec_cmd(t_shell *mini, t_list *lst)
{
	char	**temp;
	char	*str;

	if (lst->val[0][0] == '.' || lst->val[0][0] == '/')
		ft_check_cmd(mini, lst);
	else if (check_path_if_exi(mini) != NULL)
	{
		str = check_path_if_exi(mini);
		if (str != NULL)
		{
			if (find(str) == 1)
				temp = ft_split(str, ':');
			else
			{
				temp = (char **)malloc(sizeof(char *) * 2);
				temp[0] = str;
				temp[1] = NULL;
			}
			if (temp[0])
				ft_execve(temp, mini, lst);
			ft_err(lst->val[0]);
		}
	}
	else
		ft_err(lst->val[0]);
}
