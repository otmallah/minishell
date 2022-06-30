/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 23:34:59 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 02:45:57 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/minishell.h"

void	sec_utils_red(t_list **lst, char **tab, int ij, int k);

int	utils_files(t_list *list, int a, int fd, int fd_in)
{
	if (list->v_type[0] == 6)
		fd = open(list->val[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (list->v_type[0] == 4)
		fd = open(list->val[1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (list->v_type[0] == 8)
	{
		fd_in = open(list->val[1], O_RDWR, 0666);
		if (fd_in < 0)
		{
			if (a != 1)
				perror(NULL);
			fd = -1;
			return (fd);
		}
	}
	return (fd);
}

int	open_all_files(t_list *list, int a)
{
	int		fd;
	char	*str;

	fd = 1;
	while (list && list->v_type[0] != 11)
	{
		fd = utils_files(list, a, fd, 0);
		if (list->v_type[0] == 3 && a != 2)
		{
			while (1337)
			{
				str = readline("> ");
				if (str == NULL)
					break ;
				if (ft_strcmp(str, list->val[1]) == 0)
				{
					free(str);
					break ;
				}
				free(str);
			}
		}
		list = list->next;
	}
	return (fd);
}

char	**cmd_utils(t_list *list, char **tab)
{
	int	k;
	int	i;

	k = 2;
	i = 0;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4
			|| list->v_type[0] == 8 || list->v_type[0] == 3)
		{
			while (list->val[k])
			{
				tab[i++] = ft_strdup(list->val[k]);
				k++;
			}
			k = 2;
		}
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**cmd(t_list *list)
{
	int		i;
	t_list	*head;
	char	**tab;
	int		k;

	k = 2;
	i = 0;
	head = list;
	while (list && list->v_type[0] != 11)
	{
		if (list->v_type[0] == 6 || list->v_type[0] == 4
			|| list->v_type[0] == 8 || list->v_type[0] == 3)
		{
			while (list->val[k++])
				i++;
			k = 2;
		}
		else if (list->v_type[0] == 11)
			break ;
		list = list->next;
	}
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	list = head;
	return ((cmd_utils(list, tab)));
}

void	utils_red(t_list **lst)
{
	char	**tab;
	int		ij;
	int		k;

	ij = 0;
	k = 0;
	tab = cmd(*lst);
	if (tab[0])
	{
		if ((*lst)->v_type[0] == 1)
		{
			k = 1;
			while ((*lst)->val[ij])
				ij++;
		}
		if (k != 1)
		{
			ij = ft_free_lst_val(lst, ij);
			(*lst)->val = malloc(sizeof(char *) * (size_vl(tab) + 1));
			ij = 0;
		}
		sec_utils_red(lst, tab, ij, k);
	}
	else
		free(tab);
}
