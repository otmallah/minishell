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

void	check_cmd_if_built_func(t_mini *index, t_idx *id, char *str);

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
	check_cmd_if_built_func(id, idx, str);
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

int	find_len4(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

void	check_cmd_if_built_func(t_mini *index, t_idx *id, char *str)
{
	int a;
	char **tab;

	a = find_space2(str);
	if (a == 1)
	{
		tab = ft_split(str, ' ');
	}
	else
	{
		tab = (char **)malloc(sizeof(char *));
		tab[0] = str;
	}
	if (ft_strcmp(tab[0], "export") == 0)
	{
		if (a == 1)
			ft_export(index, id, tab[1]);
		else
			ft_export(index, id, NULL);
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

	a = find_len4(pipx->tab);
	i = 0;
	int ff = 0;
	while (i < a)
	{
		//puts("*-*-*-*-*-*-*-**-");
		if (pipe(fd) == -1)
			return 1;
		id = fork();
		if (id == 0)
		{
			if (i == 0)
			{
				str = ft_getenv("PATH", index);
				if (str == NULL)
				{
					printf("command not found:%s\n", pipx->tab[i]);
					break ;
				}
				else
				{
					close(fd[0]);
					dup2(0, 0);
					dup2(fd[1], STDOUT_FILENO);
					find_path(pipx->tab[i], pipx , index, idx);
				}
			}
			else if (i == (a - 1))
			{
				str = ft_getenv("PATH", index);
				if (str == NULL)
				{
					printf("command not found:%s\n", pipx->tab[i]);
				}
				else
				{
					close(fd[0]);
					close(fd[1]);
					dup2(ff, STDIN_FILENO);
					dup2(1, 1);
					find_path(pipx->tab[i], pipx , index, idx);
				}
			}
			else
			{
				str = ft_getenv("PATH", index);
				if (str == NULL)
					printf("command not found:%s\n", pipx->tab[i]);
				else
				{
					close(fd[0]);
					dup2(ff, STDIN_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					find_path(pipx->tab[i], pipx , index, idx);
				}
			}
		}
		ff = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		i++;
	}
	//close(fd[1]);
	//close(fd[0]);
	//close(fds);
	return 0;
}
