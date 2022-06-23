/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:48:55 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/19 19:48:56 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_token	*init_token(int t_type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->e_type = t_type;
	if (value)
	{
		token->val = ft_strdup(value);
		if (value)
			free(value);
	}
	else
		token->val = NULL;
	return (token);
}

t_token	*lexer_get_next_token_second(t_lexer *lexer, t_token *token)
{
	if (lexer->c == '>' && lexer->src[lexer->i + 1] == '>')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token
			(lexer, init_token(t_append, ft_strdup(">>"))));
	}
	else if (lexer->c == '>')
		return (lexer_advance_with_token(lexer, init_token
				(t_input, lexer_get_current_char_as_string(lexer))));
	else if (lexer->c == '<')
		return (lexer_advance_with_token(lexer, init_token
				(t_output, lexer_get_current_char_as_string(lexer))));
	else if (lexer->c)
		return (lexer_collect_arg(lexer));
	return (NULL);
}

t_token	*lexer_get_next_token(t_lexer *lexer, t_token *token)
{
	if (token)
		free(token);
	while (lexer->c && lexer->i < ft_strlen(lexer->src))
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (ft_error(lexer))
			return (init_token(t_error, NULL));
		else if (lexer->c == '\'' || lexer->c == '"')
			return (lexer_collect_string(lexer));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token
					(t_pip, lexer_get_current_char_as_string(lexer))));
		else if (lexer->c == '<' && lexer->src[lexer->i + 1] == '<')
		{
			lexer_advance(lexer);
			return (lexer_advance_with_token
				(lexer, init_token(t_heredoc, ft_strdup("<<"))));
		}
		else
			return (lexer_get_next_token_second(lexer, token));
	}
	return (NULL);
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}
