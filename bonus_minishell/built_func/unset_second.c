/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:57:09 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/26 20:57:39 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "../sec_parsing/header/utiles_functions.h"

void	ft_copy_tab_save_env(t_shell *index, char **temp, int n, int j)
{
	int	i;

	temp[j] = NULL;
	if (n > 0)
		free(index->tab_save_env);
	index->tab_save_env = (char **)malloc(sizeof(char *) * (tablen(temp) + 1));
	i = 0;
	while (temp[i])
	{
		index->tab_save_env[i] = ft_strdup(temp[i]);
		i++;
	}
	index->tab_save_env[i] = NULL;
}
