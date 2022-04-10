/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:35:39 by otmallah          #+#    #+#             */
/*   Updated: 2022/04/09 02:21:25 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_heredoc(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '<' && str[1] == '<')
			return 1;
		else if (str[i] == '<' && str[i + 1] == '<')
			return 2;
		i++;
	}
	return 0;
}

void    ft_heredoce(t_mini *index, t_idx *id, t_pipe *pipx, char *str)
{
	int		a;
	int sec_fd;
	char	**tab;
	char	*sec_tab;
	char	*str_read;

	FD_TE = 0;
	a = find_heredoc(str);
	if (a == 1)
	{
		tab = ft_split(str, ' ');
		sec_fd = open("he", O_CREAT | O_WRONLY , 0777);
		int fd = open(tab[4], O_CREAT | O_RDWR , 0777);
		while (1)
		{
			str_read = readline(">");
			if (strcmp(str_read, tab[1]) == 0)
				break ;
			write(sec_fd, str_read, strlen(str_read));
			write(sec_fd, "\n", 1);
		}
		close(sec_fd);
		sec_fd = open("he",  O_RDONLY);
		int idx = fork();
		if (idx == 0)
		{
			puts("/*/*/*/*/*/*//");
			dup2(sec_fd, STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			find_path_red(tab[2], pipx, index);
		}
		close(fd);
		close(sec_fd);
		wait(NULL);
	}
	//else if (a == 2)
	//{
	//	
	//}
}
