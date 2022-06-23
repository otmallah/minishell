/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:34:11 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/08 10:34:13 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

size_t	ft_strlen(char *src)
{
	size_t	i;

	i = 0;
	while (src && src[i])
		i++;
	return (i);
}

int	ft_check_error(t_lexer *lexer, int i)
{
	if (lexer->c == '<' || lexer->c == '>')
	{
		while (lexer->src[i] == ' ')
			i++;
		if (!lexer->src[i] || (lexer->src[i] == '|'
				|| ((lexer->src[i] == '>' || lexer->src[i] == '<')
					&& (lexer->src[i + 1] == '>' || lexer->src[i + 1] == '<'))
				|| (lexer->i + 1 != i && (lexer->src[i] == '<'
						|| lexer->src[i] == '>'))
				|| (lexer->src[i] == '>' && lexer->c == '<')
				|| (lexer->src[i] == '<' && lexer->c == '>')))
			return (1);
	}
	else if (lexer->c == '|')
	{
		while (lexer->src[i] == ' ')
			i++;
		if (!lexer->src[i] || lexer->src[i] == '|')
			return (1);
	}
	return (0);
}

int	ft_error(t_lexer *lexer)
{
	unsigned int	i;

	i = lexer->i + 1;
	if ((lexer->c == '|' && lexer->src[i] == '|') || lexer->c == '&')
		return (1);
	else if ((lexer->src[i] == '>' && lexer->c == '>')
		|| (lexer->src[i] == '<' && lexer->c == '<'))
	{
		while (lexer->src[i + 1] == ' ')
			i++;
		if (!lexer->src[i + 1] || lexer->src[i + 1] == '|')
			return (1);
		i = lexer->i + 1;
	}
	return (ft_check_error(lexer, i));
}
