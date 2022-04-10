/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:35:39 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/09 02:21:25 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_space2(char *tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if(tab[i] == ' ')
			return 1;
		i++;
	}
	return 0;
}

void	find_path(char *str, t_pipe *index, t_mini *id, t_idx *idx)
{
	int i;
	int a;
	char *temp;
	char **tep;

	i = 0;
	temp = getenv("PATH");
	index->tab = ft_split(temp, ':');
	int res = find_space2(str);
	//check_cmd_if_built_func(id, idx, str);
	if (res == 1)
	{
		tep = ft_split(str, ' ');
	}
	else
	{
		tep = (char **)malloc(sizeof(char *));
		tep[0] = str;
	}
	while (index->tab[i])
	{
		a = ft_strlen(index->tab[i]);
		index->tab[i][a] = '/'; // bach tkoun lpath kamla n '/'
		index->tab[i][a + 1] = '\0'; // bach nsali string
		index->str = ft_strjoin(index->tab[i], tep[0]);
		if (access(index->str, F_OK) == 0)
		{
			execve(index->str, &tep[0], index->string);
		}
		i++;
	}

}

int	find_len5(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

// void	check_cmd_if_built_func(t_mini *index, t_idx *id, char *str)
// {
// 	int a;
// 	char **tab;

// 	a = find_space2(str);
// 	if (a == 1)
// 	{
// 		tab = ft_split(str, ' ');
// 	}
// 	else
// 	{
// 		tab = (char **)malloc(sizeof(char *));
// 		tab[0] = str;
// 	}
// 	if (ft_strcmp(tab[0], "export") == 0)
// 	{
// 		if (a == 1)
// 			ft_export(index, id, tab[1]);
// 		else
// 			ft_export(index, id, NULL);
// 	}
// }

void	find_heredoc2(t_pipe *pipx, t_mini *index, t_idx *id)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (pipx->tab[i])
	{
		while (pipx->tab[i][j])
		{
			if (pipx->tab[i][j] == '<' && pipx->tab[i][j + 1] == '<')
			{
				ft_heredoce(index, id, pipx, pipx->tab[i]);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int ft_pipe(t_mini *index, t_pipe *pipx, t_idx *idx)
{
	int fd[2];
	char *str;
	int a;
	int i;
	int sp;
	int id;
	int pid[100];

	find_heredoc2(pipx, index, idx);
	a = find_len5(pipx->tab);
	i = 0;
	int ff = 0;
	while (i < a)
	{
		if (pipe(fd) == -1)
			return 1;
		id = fork();
		if (id == 0)
		{
			if (i == 0)
			{
				close(fd[0]);
				dup2(0, 0);
				dup2(fd[1], STDOUT_FILENO);
				find_path(pipx->tab[i], pipx , index, idx);
			}
			else if (i == (a - 1))
			{
				close(fd[0]);
				close(fd[1]);
				dup2(ff, STDIN_FILENO);
				dup2(1, 1);
				find_path(pipx->tab[i], pipx , index, idx);
			}
			else
			{
				close(fd[0]);
				dup2(ff, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				find_path(pipx->tab[i], pipx , index, idx);
			}
		}
		pid[i] = id;
		ff = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		// wait(NULL);
		i++;
	}
	//while (wait(NULL) != -1)
	while (--i >= 0)
		waitpid(pid[i], 0, 0);
	return 0;
}

int		find_pipe(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return 1;
		i++;
	}
	return 0;
}

void	check_pipe(t_pipe *pipe, t_mini *index, t_idx *id, char *str)
{
	int a;

	a = find_pipe(str);
	if (a == 1)
	{
		pipe->tab = ft_split(str, '|');
		ft_pipe(index, pipe, id);
	}
}


int main(int ac, char **av, char **env)
{
	t_mini index;
	t_idx id;
	t_pipe pipx;

	index.count2 = 0;
	index.finde = NULL;
	index.tab_exp = env;
	index.string = env;
	index.tab_unset = env;
	id.c = 0;
	id.cnt = 0;
	id.a = 0;
	id.b = 0;
	id.d = 0;
	id.poor = 1;
	id.cot = 0;
	check_pipe(&pipx, &index, &id, av[1]);
}
