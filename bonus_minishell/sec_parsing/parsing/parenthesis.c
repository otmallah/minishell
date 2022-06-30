/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:54:43 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/23 19:54:45 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*delet_parenthesis(char *str, char *tab)
{
	char	*tmp;
	int		i;
	int		n;

	free(tab);
	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
			n++;
		i++;
	}
	tmp = malloc(sizeof(char) * n + 1);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')')
			tmp[n++] = str[i];
		i++;
	}
	tmp[n] = '\0';
	return (tmp);
}

char	*check_parenthesis_second(char *tab, char *str, int i, int n)
{
	while (str[i] && n >= 0)
	{
		if (str[i] == '(' && str[i + 1] == ')')
			return (NULL);
		else if (str[i] == '(')
			tab[n++] = '(';
		else if (str[i] == ')')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (!tab[--n] || (str[i] && (str[i] != '&' && str[i] != '|'
						&& str[i] != '>' && str[i] != '<' && str[i] != ' '
						&& str[i] != ')')))
				return (free_string(tab));
			else if (tab[n] == '(')
				tab[n] = '\0';
			if (str[i] == ')' && tab[--n] == '(')
				tab[n] = '\0';
		}
		i++;
	}
	if (n != 0 || (!str[0] && tab[n] == '('))
		return (free_string(tab));
	return (str);
}

char	*check_parenthesis(char *str)
{
	int		i;
	int		n;
	char	*tab;

	i = 0;
	n = 0;
	tab = malloc(sizeof(char) * (ft_strlen(str) + 1));
	tab[ft_strlen(str) + 1] = '\0';
	if (!check_parenthesis_second(tab, str, i, n))
		return (NULL);
	return (delet_parenthesis(str, tab));
}
