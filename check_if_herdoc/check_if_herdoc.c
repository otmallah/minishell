/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 02:34:02 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/27 02:34:09 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sec_parsing/header/minishell.h"

int	finder_red(t_list *list)
{
	while (list)
	{
		if (list && (list->v_type[0] == 6 || list->v_type[0] == 4))
			return (2);
		else if (list && list->v_type[0] == 8)
			return (3);
		else if (list && list->v_type[0] == 3)
			return (4);
		list = list->next;
	}
	return (0);
}
