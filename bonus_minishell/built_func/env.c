/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:13:55 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/26 04:13:45 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_env(t_shell *index, int fd)
{
	int	i;

	i = 0;
	while (index->tab_save_env[i])
	{
		ft_putendl_fd(index->tab_save_env[i], fd);
		i++;
	}
	if (index->tab_save_exp)
	{
		i = 0;
		while (index->tab_save_exp[i])
		{
			if (len(index->tab_save_exp[i]) != 0)
				ft_putendl_fd(index->tab_save_exp[i], fd);
			i++;
		}
	}
}

void	add_name2(int i, char *str)
{
	if (i != -1 && ft_strcmp(str, "exit") != 0)
	{
		g_id.g_status_exec = 127;
		g_id.failer = 2;
		g_id.id = 0;
	}
}
