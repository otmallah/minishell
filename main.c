
#include "minishell.h"

char	*find_PATH(char **env)
{
	int i;
	char *tab;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H')
			tab = env[i];
		i++;
	}
	return (tab);
}

int main(int ac, char **av, char **env)
{
	int i;
	char *str;
	char **tab;
	char buff[256];
	i = 0;

	if (strcmp(av[1], "pwd") == 0)
		ft_pwd();
	if (strcmp(av[1], "cd") == 0)
	{
		puts(" ok ");
		ft_cd(av[2]);
	}
	str = find_PATH(env);
	tab = ft_split(str, ':');
	i = 0;
	while (tab[i])
	{
	    str = ft_strjoin(tab[i], av[1]);
	    if (access(str, F_OK) == 0)
	        execve(str, &av[1], env);
	    i++;
	}
}