/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:11:51 by otmallah          #+#    #+#             */
/*   Updated: 2022/03/18 18:11:52 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_cd(char *path)
{
    int a;
    char buff[256];

    //printf("path %s\n", getcwd(buff, sizeof(buff)));
    a = chdir(path);
    if (a != 0)
        perror("error ");
    //printf("path %s\n", getcwd(buff, sizeof(buff)));
}
