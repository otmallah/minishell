
#include "minishell.h"

char *ft_getenv(char *str, t_mini *index);

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

int    find_space(char *str);

void    func_all(t_mini *index, char *str)
{
	int i;
	int a;
	int res;
	char **test;
	char *str2;

	i = 0;
	res = find_space(str);
	if (res == 1)
		test = ft_split(str, ' ');
	else
	{
		test = (char **)malloc(sizeof(char *) * 1);
		test[0] = str;
	}
	while (index->tab[i])
	{
		a = ft_strlen(index->tab[i]);
		index->tab[i][a] = '/'; // bach tkoun lpath kamla n '/'
		index->tab[i][a + 1] = '\0'; // bach nsali string
		index->str = ft_strjoin(index->tab[i], test[0]);
		if (access(index->str, F_OK) == 0)
		{
			execve(index->str, &test[0], index->string);
		}
		i++;
	}
	printf("command not found:%s\n", test[0]);
}

int    find_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return 1;
		i++;
	}
	return 2;
}


//void handler(int sig)
//{
//	if (sig == 2)
//		printf("hana hh\n");
//}

int main(int ac, char **av, char **env)
{
	t_mini index;
	t_idx id;
	char *str;
	int a = 0;
	char **tmp;
	t_list *list;
	t_list *list2;

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
	list = NULL;
	list2 = NULL;
	while (1)
	{
		//signal(SIGINT, handler);
		str = readline("minishell >$ ");
		//signal(SIGINT, handler);
		if (str)
		{
			add_history(str);
			a = find_space(str);
			if (a == 1)
				tmp = ft_split(str, ' ');
			else
			{
				tmp = (char **)malloc(sizeof(char *));
				tmp[0] = str;
			}
			if (ft_strcmp(tmp[0] , "echo") == 0  && ft_strcmp(tmp[1] , "-n") == 0)
				built_func(tmp[2]);
			else if (ft_strcmp(tmp[0], "env") == 0)
				ft_env(&index, &id);
			else if (ft_strcmp(tmp[0], "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(tmp[0], "cd") == 0)
				ft_cd(tmp[1]);
		   	else if (ft_strcmp(tmp[0], "export") == 0)
		   	{
				if (a == 1)
		   			ft_export(&index, &id, tmp[1]);
				else
				   ft_export(&index, &id, NULL);
			}
			else if (ft_strcmp(tmp[0], "exit") == 0)
				ft_exit();
			else if (ft_strcmp(tmp[0], "unset") == 0)
			{
				if (tmp[1])
					ft_unset(&index, &id, tmp[1]);
			}
			else
			{
				if (fork() == 0) // hna dert l fork bach n3ty child executy li cmd o ikhali main proc khedam
				{
					index.str = ft_getenv("PATH", &index);
					if (index.str == NULL)
						printf("command not found:\n");
					else
					{
						index.tab = ft_split(index.str, ':');
						func_all(&index, str);
					}
				}
				wait(NULL); // hadi bach itsana hta isali childe 3ad i trunna parent
			}
		}
	}
}

char *ft_getenv(char *str, t_mini *index)
{
	int i;
	char *temp;

	i = 0;
	while (index->string[i])
	{
		puts("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
		temp = ft_substr(index->string[i], 0, find_len3(index->string[i]));
		if (ft_strcmp(temp, str) == 0)
			return (ft_strchr(index->string[i], '/'));
		i++;
	}
	return NULL;
}