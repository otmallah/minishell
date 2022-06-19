/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:34:11 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/08 10:34:13 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	ft_error(lexer_t *lexer)
{
	unsigned int i;

	i = lexer->i + 1;
	if ((lexer->c == '|' && lexer->src[i] == '|') || lexer->c == '&')
		return (1);
	else if ((lexer->src[i] == '>' && lexer->c == '>') || (lexer->src[i] == '<' && lexer->c == '<'))
	{
		while (lexer->src[i + 1] == ' ')
            i++;
		if (!lexer->src[i + 1])
			return (1);
		i = lexer->i + 1;
	}
	if (lexer->c == '<' || lexer->c == '>')
	{
		while (lexer->src[i] == ' ')
            i++;
		if ( !lexer->src[i] || (lexer->src[i] == '|' 
			|| ((lexer->src[i] == '>' || lexer->src[i] == '<')
			&& (lexer->src[i + 1] == '>' || lexer->src[i + 1] == '<'))
			|| (lexer->i + 1 != i && (lexer->src[i]  == '<' || lexer->src[i]  == '>'))
			|| (lexer->src[i] == '>' && lexer->c == '<')
			|| (lexer->src[i] == '<' && lexer->c == '>')))
			return (1);
	}
	else if (lexer->c == '|')
    {
        while (lexer->src[i] == ' ')
            i++;
        if(!lexer->src[i]  || lexer->src[i] == '|')
            return (1);
	}
	return (0);
}