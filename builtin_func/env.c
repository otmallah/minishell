/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:08:26 by otmallah          #+#    #+#             */
/*   Updated: 2022/03/18 21:08:27 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_env(t_mini *index)
{
    int i;

    i = 0;
    while (index->string[i])
    {
        printf("%s\n", index->string[i]);
        i++;
    }
    if (index->finde != NULL)
        printf("%s\n" , index->finde);
}
