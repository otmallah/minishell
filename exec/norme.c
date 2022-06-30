/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:08:50 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 02:38:48 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/minishell.h"

int	utils_true_while(void);

void	sec_utils_red(t_list **lst, char **tab, int ij, int k)
{
	int	io;

	io = 0;
	while (tab[io])
	{
		if (k == 1)
		{
			(*lst)->val = ft_realloc_char((*lst)->val);
			(*lst)->val[ij++] = ft_strdup(tab[io++]);
			free(tab[io - 1]);
		}
		else
		{
			(*lst)->val[ij++] = ft_strdup(tab[io++]);
			free(tab[io - 1]);
		}
	}
	(*lst)->val[ij] = NULL;
	(*lst)->v_type[0] = 1;
	(*lst)->v_type[1] = 2;
	free(tab);
}

int	utiiiils(int size, char *find)
{
	int	fd;

	if (size == 0)
	{
		free(find);
		return (1);
	}
	else
	{
		fd = open("/tmp/test", O_RDWR | O_TRUNC, 0644);
		return (fd);
	}
}

void	ft_dup_g_fd(int fd, char **tab)
{
	fd = 0;
	dup(g_id.g_fd);
	ft_free(tab);
}

void	true_while(char **tab, int size)
{
	char	*find;
	int		fd;
	int		i;

	i = 0;
	fd = utils_true_while();
	g_id.cheecker = 1;
	while (1)
	{
		find = readline("> ");
		if (find == NULL)
			break ;
		if (ft_strcmp(find, tab[i]) == 0 && tab[i])
		{
			size--;
			i++;
			if (utiiiils(size, find) == 1)
				break ;
			fd = utiiiils(size, find);
		}
		if (size != 0)
			ft_putendl_fd(find, fd);
		free(find);
	}
	ft_dup_g_fd(g_id.g_fd, tab);
}
