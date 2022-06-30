/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:57:56 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/26 04:31:50 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sec_parsing/header/minishell.h"

void	ft_handler_signal_second(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_id.g_status_exec = 1;
	}
	else if (sig == SIGQUIT && g_id.cheecker == 0)
	{
		write(1, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler(int sig)
{
	if ((sig == SIGINT || sig == SIGQUIT) && g_id.id != 0
		&& g_id.cheecker == 0 && g_id.g_status_exec != 127)
	{
		if (sig == SIGQUIT)
			write (1, "Quit: 3\n", 9);
		if (sig == SIGINT)
			write(1, "\n", 1);
		kill(g_id.id, 9);
		g_id.g_status_exec = 130;
	}
	else if (g_id.cheecker == 1 && sig != SIGQUIT)
	{
		write (1, "\n", 1);
		close(0);
		g_id.cheecker = 0;
	}
	else
		ft_handler_signal_second(sig);
	if (sig != SIGQUIT)
		g_id.cheecker = 0;
	g_id.id = 0;
}

void	ft_mini(t_shell *mini, char *src)
{
	t_list	*lst;
	t_list	*head;

	lst = ft_parser(src, mini);
	head = lst;
	if (!lst)
		return ;
	else if (finde_her(lst) == 1)
		pipes(mini, lst);
	else if (finder_red(lst) == 2)
		ft_redirection(mini, lst, 0, 1);
	else if (finder_red(lst) == 4)
		heredoc(mini, lst, 0, 1);
	else if (finder_red(lst) == 3)
		ft_redin(mini, lst, 1, 0);
	else
	{
		ft_exit_status(mini, lst);
		ft_check_built(mini, lst, 1);
	}
	ft_free_list(head);
}

void	initialiation_mini(t_shell *mini, char **env)
{
	mini->tab_save_env = env;
	mini->tab_save_exp = NULL;
	mini->counter = 0;
	mini->num_ofall_cmd = 0;
	mini->num_cmd = 0;
	mini->cnt = 0;
	mini->fs = 0;
	mini->built = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*src;
	t_shell	mini;

	(void)ac;
	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	initialiation_mini(&mini, env);
	while (1337)
	{
		mini.counter = 0;
		g_id.id = 0;
		g_id.g_fd = dup(0);
		src = readline("minishell : ");
		if (errno == 13)
			g_id.g_status_exec = 126;
		if (src == NULL)
			ft_exit_prg();
		ft_mini(&mini, src);
		add_history(src);
		free(src);
	}
	return (0);
}
