/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:34:11 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/24 10:34:33 by otmallah         ###   ########.fr       */
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

int	ft_check_error_second(t_lexer *lexer, int i)
{
	if (lexer->c == '&')
	{
		if (lexer->src[i] == '&')
			i++;
		while (lexer->src[i] == ' ')
			i++;
		if (!lexer->src[i] || lexer->src[i] == '|' || lexer->src[i] == '&')
			return (1);
	}
	return (0);
}

int	ft_check_error(t_lexer *lexer, int i)
{
	if (lexer->c == '<' || lexer->c == '>')
	{
		while (lexer->src[i] == ' ')
			i++;
		if (!lexer->src[i] || lexer->src[i] == '&' || (lexer->src[i] == '|'
				|| ((lexer->src[i] == '>' || lexer->src[i] == '<')
					&& (lexer->src[i + 1] == '>' || lexer->src[i + 1] == '<'))
				|| (lexer->i + 1 != (unsigned int)i && (lexer->src[i] == '<'
						|| lexer->src[i] == '>'))
				|| (lexer->src[i] == '>' && lexer->c == '<')
				|| (lexer->src[i] == '<' && lexer->c == '>')))
			return (1);
	}
	else if (lexer->c == '|')
	{
		if (lexer->src[i] == '|')
			i++;
		while (lexer->src[i] == ' ')
			i++;
		if (!lexer->src[i] || lexer->src[i] == '|' || lexer->src[i] == '&')
			return (1);
	}
	else
		return (ft_check_error_second(lexer, i));
	return (0);
}

int	ft_error(t_lexer *lexer)
{
	unsigned int	i;

	i = lexer->i + 1;
	if ((lexer->c == '|' && lexer->src[i] == '|' && lexer->src[i + 1] == '|')
		|| (lexer->c == '&' && lexer->src[i] != '&'))
		return (1);
	else if ((lexer->src[i] == '>' && lexer->c == '>')
		|| (lexer->src[i] == '<' && lexer->c == '<'))
	{
		while (lexer->src[i + 1] == ' ')
			i++;
		if (!lexer->src[i + 1] || lexer->src[i + 1] == '|'
			|| lexer->src[i + 1] == '&')
			return (1);
		i = lexer->i + 1;
	}
	return (ft_check_error(lexer, i));
}

t_list	*print_error(char *str, t_lexer *lexer, t_token *token, t_list *lst)
{
	g_id.g_status_exec = 127;
	printf("parse error %s\n", str);
	if (lexer)
		free(lexer);
	if (token)
	{
		if (token->val)
			free(token->val);
		free(token);
	}
	if (lst)
		ft_free_list(lst);
	return (NULL);
}
