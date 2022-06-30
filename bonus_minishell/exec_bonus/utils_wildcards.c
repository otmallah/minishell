/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:25:31 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 10:32:54 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	change(t_list **list, t_wild *wild)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = strdup((*list)->val[0]);
	ft_free((*list)->val);
	(*list)->val = malloc(sizeof(char *) * (size_vl(wild->tab_wild) + 2));
	while (wild->tab_wild[i])
	{
		if (j == 0)
			(*list)->val[j] = temp;
		else
		{
			(*list)->val[j] = strdup(wild->tab_wild[i]);
			i++;
		}
		j++;
	}
	(*list)->val[j] = NULL;
	(*list)->v_type[0] = 1;
	(*list)->v_type[1] = 2;
}

int	sec_utils_wild(t_wild *wild, int i, int count, char **tab)
{
	int		size;

	size = size_vl(tab);
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
	return (count);
}

void	utils_milt_wild(t_wild *wild, char **tab, int fd)
{
	int	i;
	int	count;
	int	size;

	i = 0;
	count = 0;
	wild->get_next = get_next_line(fd);
	size = size_vl(tab);
	while (wild->get_next != NULL)
	{
		while (tab[i])
			count = sec_utils_wild(wild, i++, count, tab);
		i = 0;
		if (count == size)
		{
			wild->tab_wild[wild->size_j] = strdup(wild->get_next);
			wild->tab_wild[wild->size_j + 1] = NULL;
			wild->size_j++;
			wild->tab_wild = ft_realloc_char(wild->tab_wild);
		}
		count = 0;
		free(wild->get_next);
		wild->get_next = get_next_line(fd);
	}
}

void	utils_mult_wild(t_list **list, t_wild *wild, char *tab, int fd)
{
	close(fd);
	fd = open("/tmp/test1", O_RDWR, 0644);
	wild->get_next = get_next_line(fd);
	while (wild->get_next != NULL)
	{
		wild->size = ft_strlen(tab);
		if ((*list)->val[1][0] != '*')
			wild->str1 = ft_strstr2(wild->get_next, tab, wild->size);
		else
			wild->str1 = ft_strstr(wild->get_next, tab, wild->size);
		if (wild->str1 != NULL)
		{
			wild->tab_wild[wild->size_j] = strdup(wild->get_next);
			wild->tab_wild[wild->size_j + 1] = NULL;
			wild->size_j++;
			wild->tab_wild = ft_realloc_char(wild->tab_wild);
		}
		free(wild->get_next);
		wild->get_next = get_next_line(fd);
	}
}

void	mult_wild(t_list **list, t_wild *wild, char **tab, int fd)
{
	int	i;
	int	k;

	i = 0;
	k = size_vl(tab);
	if (k > 1)
		utils_milt_wild(wild, tab, fd);
	else
	{
		while (tab[i])
		{
			utils_mult_wild(list, wild, tab[i], fd);
			i++;
		}
	}
}
