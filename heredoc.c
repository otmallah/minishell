/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:35:39 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/08 17:15:07 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_heredoc(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return 1;
		i++;
	}
	return 0;
}

void    ft_heredoce(t_mini *index, t_idx *id, t_pipe *pipx, char *str)
{
	int		ID_FORK;
	int		a;
	char	**tab;
	char	*sec_tab;
	char	*str_read;
	int		FD_DUP;
	int		FD;

	a = find_heredoc(str);
	if (a == 1)
	{
		tab = ft_split(str, ' ');
		FD_TE = open("he", O_CREAT | O_RDWR , 0777);
		FD = open(tab[4], O_CREAT | O_RDWR , 0777);
		while (1)
		{
			str_read = readline(">");
			if (strcmp(str_read, tab[1]) == 0)
				break ;
			write(FD_TE, str_read, strlen(str_read));
			write(FD_TE, "\n", 1);
		}
		ID_FORK = fork();
		if (ID_FORK == 0)
		{
			dup2(FD_TE, STDIN_FILENO);
			dup2(FD, STDOUT_FILENO);
			find_path_red(tab[2], pipx, index);
		}
		wait(NULL);
		close(FD_TE);
		//ft_redirections(index, id, pipx, sec_tab);
	}
}

int main(int ac, char **av)
{
	t_mini index;
	t_idx id;
	t_pipe pipx;

	ft_heredoce(&index, &id, &pipx, av[1]);
}