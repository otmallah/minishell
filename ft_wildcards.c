/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 01:09:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/23 04:48:18 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "sec_parsing/header/utiles_functions.h"

typedef struct  s_wild
{
	char    *get_next;
	char    *str1;
	char    *str2;
	char    **tab_wild;
	int     size;
	int		size_j;
}   t_wild;

void	change(t_list **list, t_wild *wild)
{
	int i;
	int	j;
	char *temp;

	i = 0;
	j = 0;
	temp = (*list)->val[0];
	(*list)->val = malloc(sizeof(char *) * (size_vl(wild->tab_wild) + 1));
	while (wild->tab_wild[i])
	{
		if (j == 0)
			(*list)->val[j] = ft_strdup(temp);
		else
		{
			(*list)->val[j] = ft_strdup(wild->tab_wild[i]);
			i++;
		}
		j++;
	}
	(*list)->val[j] = NULL;
	(*list)->v_type[0] = 1;
	(*list)->v_type[1] = 2;
}

int	utils_milt_wild(t_list **list, t_wild *wild, char **tab, int fd)
{
	int	i;
	int	j;
	int	count;
	int	size;

	i = 0;
	j = 0;
	count = 0;
	wild->get_next = get_next_line(fd);
	size = size_vl(tab);
	while (wild->get_next != NULL)
	{
		while(tab[i])
		{
			if (i == 0)
			{
				wild->size = ft_strlen(tab[i]);
				wild->str1 = ft_strstr2(wild->get_next, tab[i], wild->size);
				if (wild->str1)
					count++;
			}
			else if (i == (size - 1))
			{
				wild->size = ft_strlen(tab[i]);
				wild->str1 = ft_strstr(wild->get_next, tab[i], wild->size);
				if (wild->str1)
					count++;
			}
			else
			{
				wild->size = ft_strlen(tab[i]);
				wild->str1 = ft_strstr3(wild->get_next, tab[i], wild->size);
				if (wild->str1)
					count++;
			}
			i++;		
		}
		i = 0;
		if (count == size)
		{
			wild->tab_wild[wild->size_j] = ft_strdup(wild->get_next);
			wild->size_j++;
		}
		count = 0;
		wild->get_next = get_next_line(fd);
	}
	return (j);
}

void	mult_wild(t_list **list, t_wild *wild, char **tab, int fd)
{
	int i;
	int	j;
	int k;

	i = 0;
	j = 0;
	k = size_vl(tab);
	if (k > 1)
		j = utils_milt_wild(list, wild, tab, fd);
	else
	{
		while (tab[i])
		{
			wild->get_next = get_next_line(fd);
			while (wild->get_next != NULL)
			{
				wild->size = ft_strlen(tab[i]);
				wild->str1 = ft_strstr2(wild->get_next, tab[i], wild->size);
				if (wild->str1)
				{
					wild->tab_wild[wild->size_j] = strdup(wild->get_next);
					wild->size_j++;
				}
				wild->get_next = get_next_line(fd);
			}
			i++;
		}
	}
}

void    import_all_arg(t_shell *mini, t_list **list, t_wild *wild, int fd)
{
	char    **tab;
	int     k;
	int		j;

	k = 1;
	while (*list && (*list)->val[k])
	{
		tab = ft_split((*list)->val[k], '*');
		mult_wild(list, wild, tab, fd);
		close(fd);
		fd = open("/tmp/test1", O_RDWR, 0644);
		k++;
	}
	wild->tab_wild[wild->size_j] = NULL;
	if (wild->size_j != 0)
		change(list, wild);
}

void	exec_wild(t_shell *mini, t_list *list)
{
	char	**temp;
	char	*str;

	str = check_path_if_exi(mini);
	if (str)
	{
		temp = ft_split(str, ':');
		if (temp[0])
			ft_execve(temp, mini, list);
		ft_err(list->val[0]);
	}
}

void    ft_wildcards(t_list **list, t_shell *mini)
{
	char    **tab;
	char    *exec[] = {"ls", NULL};
	int     fd;
	int     i;
	int     j;
	t_wild  wild;

	i = 0;
	j = 1;
	wild.size = 0;
	wild.size_j = 0;
	wild.tab_wild = (char **)malloc(sizeof(char *) * 50);
	unlink("/tmp/test1");
	fd = open("/tmp/test1", O_CREAT | O_RDWR, 0644);
	if (fork() == 0)
	{
		dup2(fd, 1);
		execve("/bin/ls", exec, mini->tab_save_env);
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
	close(fd);
	fd = open("/tmp/test1", O_RDWR, 0644);
	import_all_arg(mini, list, &wild, fd);
	if (fork() == 0)
		exec_wild(mini, *list);
	wait(NULL);
}
