
#include "minishell.h"

void	built_func(char *av)
{
	//if (ft_strcmp(av, "pwd") == 0)
	//	ft_pwd();
	//if (ft_strcmp(av, "cd") == 0)
	//{
	//	ft_cd(av2);
	//}
	ft_echo(av);
	//if (ft_strcmp(av, "exit") == 0)
	//	ft_exit();
	//if (ft_strcmp(av, "env") == 0)
	//	ft_env(index);
}

void    func_all(t_mini *index, char *str)
{
    int i;
    int a;
    char **test;

    i = 0;
    test = ft_split(str, ' ');
    while (index->tab[i])
	{
	    a = ft_strlen(index->tab[i]);
	    index->tab[i][a] = '/';
	    index->tab[i][a + 1] = '\0';
	    index->str = ft_strjoin(index->tab[i], test[0]);
	    if (access(index->str, F_OK) == 0)
	    {
	        execve(index->str, &test[0], index->string);
	    }
	    i++;
	}
}

int main(int ac, char **av, char **env)
{
    t_mini index;
    char *str;
    char **tmp;

    while (1)
    {
        //fork();
        str = readline("minishell >$ ");
        if (str)
        {
            add_history(str);
            tmp = ft_split(str, ' ');
            if (ft_strcmp(tmp[0] , "echo") == 0  && ft_strcmp(tmp[1] , "-n") == 0)
                built_func(tmp[2]);
            else if (ft_strcmp(tmp[0], "env") == 0)
            {
               index.string = env;
                ft_env(&index);
            }
            else if (ft_strcmp(tmp[0], "pwd") == 0)
                ft_pwd();
            else if (ft_strcmp(tmp[0], "cd") == 0)
                ft_cd(tmp[1]);
            else
            {
                if (fork() == 0)
                {
                    index.string = env;
                    index.str = getenv("PATH");
	                index.str = ft_strchr(index.str, '/');
	                index.tab = ft_split(index.str, ':');
                    func_all(&index, str);
                }
                wait(NULL);
            }
        }
        //index.str = getenv("PATH");
	    //index.str = ft_strchr(index.str, '/');
	    //index.tab = ft_split(index.str, ':');
        //func_all(&index, str, env);
    }
}