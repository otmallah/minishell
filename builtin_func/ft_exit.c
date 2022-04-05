/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:10:58 by otmallah          #+#    #+#             */
/*   Updated: 2022/03/18 21:10:59 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_exit(t_mini *index)
{
    if (index->tab_e)
    {
        free(index->tab_e);
        free(index->env_tab);
        free(index->tab_exp);
    }
    printf("exit\n");
    exit(1);
}