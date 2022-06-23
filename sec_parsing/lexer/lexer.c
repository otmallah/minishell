/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:39:13 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/19 19:39:14 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_lexer	*init_lexer(char *src, t_shell *mini)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->src = src;
	lexer->i = 0;
	lexer->c = src[lexer->i];
	lexer->mini = mini;
	return (lexer);
}

int	is_allnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '*' || c == '?')
		return (1);
	return (0);
}

char	*lexer_collect_arg_second(t_lexer *lexer, t_token *token, char *str)
{
	char	*tmp;

	check_backslash(&lexer);
	tmp = lexer_get_current_char_as_string(lexer);
	str = ft_h_strjoin(str, tmp);
	free(tmp);
	lexer_advance(lexer);
	if (lexer->c == '"' || lexer->c == '\'')
	{
		token = lexer_collect_string(lexer);
		if (ft_free_token_and_string(token, str, 0))
			return (NULL);
		str = ft_h_strjoin(str, token->val);
		ft_free_token_and_string(token, str, 1);
	}
	return (str);
}

t_token	*lexer_collect_arg(t_lexer *lexer)
{
	char	*str;
	t_token	*token;

	str = NULL;
	while (lexer->src[lexer->i] && lexer->c != ' ' && lexer->c != '|'
		&& lexer->c != '>' && lexer->c != '<')
	{
		if (lexer->c == '$' && is_allnum(lexer->src[lexer->i + 1]))
		{
			str = check_arg_dollar(lexer, str, 0);
			if (!str)
				return (init_token(t_error, NULL));
		}	
		else if (lexer->c == '$' && lexer->src[lexer->i + 1] == '\\')
			return (init_token(t_error, NULL));
		else
		{
			str = lexer_collect_arg_second(lexer, token, str);
			if (!str)
				return (init_token(t_error, NULL));
		}
	}
	return (init_token(t_args, str));
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
