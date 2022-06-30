/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_utils_wild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 04:48:10 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 09:20:23 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	err_wild(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": minishell : no such file or directory\n", 41);
}

void	add_name(int i, char *str)
{
	if (i != -1 && ft_strcmp(str, "exit") != 0)
	{
		g_id.g_status_exec = 127;
		g_id.failer = 2;
	}
}
