/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:12:10 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/05 22:17:37 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_red(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '>')
            return 1;
        i++;
    }
	return 0;
}

int	find_space5(char *tab)
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

void	find_path_red(char *str, t_pipe *index, t_mini *id)
{
	int i;
	int a;
	char *temp;
	char **tep;

	i = 0;
	temp = getenv("PATH");
	index->tab = ft_split(temp, ':');
	int res = find_space5(str);
	if (res == 1)
	{
		tep = ft_split(str, ' ');
	}
	else
	{
		tep = (char **)malloc(sizeof(char *));
		tep[0] = str;
	}
	//check_cmd_if_built_func(id, tep);
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

void	ft_redirections(t_mini *index, t_idx *id, t_pipe *pipx, char *str)
{
    int a;
	int ID_FOR;
    char **tab;
	char *TEMP;

    a = find_red(str);
    if (a == 1) 
    {
		if (str[0] == '>')
		{
			tab = ft_split(str, '>');
			int fd = open(tab[0], O_CREAT | O_RDWR , 0777);
			while (1)
			{
				TEMP = readline("");
				if (ft_strcmp(TEMP, "stop") == 0)
					break ;
				write (fd, TEMP, ft_strlen(TEMP));
				write (fd, "\n", 1);
			}
		}
		else
		{
        	tab = ft_split(str, '>');
        	int fd = open(tab[1], O_CREAT | O_RDWR , 0777);
			if (ft_strcmp(tab[0], "export") == 0)
			{
				dup2(fd, STDOUT_FILENO);
				ft_export(index, id, NULL);
				dup2(STDOUT_FILENO, fd);
				close(fd);
			}
			else
			{
				ID_FOR = fork();
				if (ID_FOR == 0)
				{
        			dup2(fd, STDOUT_FILENO);
        			find_path_red(tab[0], pipx, index);
				}
				wait(NULL);
			}
		}
    }
}