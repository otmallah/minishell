
#include "minishell.h"

void	built_func(char *av, char *av2, char *av3)
{
	if (strcmp(av, "pwd") == 0)
		ft_pwd();
	if (strcmp(av, "cd") == 0)
		ft_cd(av2);
	if (strcmp(av, "echo") == 0 && strcmp(av2 ,"-n") == 0)
	{
		//puts("hana");
		printf("%s", av3);
		exit(0);
	}
	if (strcmp(av, "exit") == 0)
		ft_exit();
}

int main(int ac, char **av, char **env)
{
	t_mini index;
	int i;
	int a;

	i = 0;
	//built_func(av[1], av[2], av[3]);
	printf("PATH : %s\n", getenv(" "));
	index.str = getenv("PATH");
	index.str = ft_strchr(index.str, '/');
	index.tab = ft_split(index.str, ':');
	char *tes = ttyname(0);
	printf("tes %s \n" , tes);
	while (index.tab[i])
	{
		a = ft_strlen(index.tab[i]);
		index.tab[i][a] = '/';
		index.tab[i][a + 1] = '\0';
	    index.str = ft_strjoin(index.tab[i], av[1]);
	    if (access(index.str, F_OK) == 0)
		{
	        execve(index.str, &av[1], env);
		}
		i++;
	}
}