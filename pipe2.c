#include "pipe.h"

typedef	struct s_solo {
	char **string;
	char	**tab;
	char	*str;
}	t_solo;

void	find_path(char *str, t_solo *index)
{
	int i;
	int a;
	char *temp;
	char **tep;

	i = 0;
	temp = getenv("PATH");
	//printf("%s\n", temp);
	index->tab = ft_split(temp, ':');
	tep = (char **)malloc(sizeof(char *));
	tep[0] = str;
	while (index->tab[i])
	{
		a = ft_strlen(index->tab[i]);
		index->tab[i][a] = '/'; // bach tkoun lpath kamla n '/'
		index->tab[i][a + 1] = '\0'; // bach nsali string
		index->str = ft_strjoin(index->tab[i], str);
		if (access(index->str, F_OK) == 0)
		{
			puts("hana");
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
	char *str[] = {av[1], NULL};
	t_solo index;

	if (pipe(fd) == -1)
		return 1;
	fds = open("file.txt", O_CREAT | O_RDWR, 0777);
	index.string = env;
	tab = ft_split(av[1], '|');
	a = find_len(tab);
	i = 0;
	while (i < a)
	{
		if (i == 0)
		{
			id = fork();
			if (id == 0)
			{
				printf("%s\n", tab[i]);
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				find_path(tab[i], &index);
			}
			wait(NULL);
		}
		else if (i == (a - 1))
		{
			//puts("hana");
			wait(NULL);
			close(fd[1]);
			close(fd[0]);
			id = fork();
			if (id == 0)
			{
				dup2(fd[0], 0);
				dup2(1, fd[1]);
				printf("%s\n", tab[i]);
				find_path(tab[i], &index);
			}
			wait(NULL);
		}
		else
		{
			close(fd[1]);
			id = fork();
			if (id == 0)
			{
				printf("%s\n", tab[i]);
				dup2(fd[0], 0);
				find_path(tab[i], &index);
			}
			wait(NULL);
		}
		i++;
	}
	close(fd[1]);
	close(fd[0]);
	close(fds);
}
