#include "pipe.h"

typedef	struct s_solo {
	char **string;
	char	**tab;
	char	*str;
}	t_solo;

int	find_space(char *tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if(tab[i] == ' ');
			return 1;
		i++;
	}
	return 0;
}

void	find_path(char *str, t_solo *index)
{
	int i;
	int a;
	char *temp;
	char **tep;

	i = 0;
	temp = getenv("PATH");
	index->tab = ft_split(temp, ':');
	int res = find_space(str);
	if (res = 1)
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

int	find_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return i;
}

int main(int ac, char **av ,char **env)
{
	int fd[2];
	int fds;
	int a;
	int i;
	int id;
	char **tab;
	t_solo index;

	//if (pipe(fd) == -1)
	//	return 1;
	index.string = env;
	tab = ft_split(av[1], '|');
	a = find_len(tab);
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
				//printf("tab = %s\n", tab[i]);
				dup2(0, 0);
				dup2(fd[1], STDOUT_FILENO);
				find_path(tab[i], &index);
				//dup2(0, fd[0]);
			}
			else if (i == (a - 1))
			{
				printf("tab = %s\n", tab[i]);
				close(fd[0]);
				close(fd[1]);
				dup2(ff, STDIN_FILENO);
				dup2(1, 1);
				find_path(tab[i], &index);
			}
			else
			{
				//printf("%s\n", tab[i]);
				close(fd[0]);
				dup2(ff, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				find_path(tab[i], &index);
				//dup2(0, fd[0]);
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
}
