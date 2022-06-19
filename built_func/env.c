/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:13:55 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/17 11:52:24 by otmallah         ###   ########.fr       */
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
