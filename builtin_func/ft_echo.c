/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:11:23 by otmallah          #+#    #+#             */
/*   Updated: 2022/03/18 18:11:24 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *str)
{
	int i;
	char *find;
	
	i = 0;
	if (str[i] != '$')
		printf("%s", str);
	else
	{
		i++;
		find = getenv(str + i);
		if (find == NULL)
			printf("\n");
		else
			printf("%s" , find);
	}
}
