/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:17 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/15 22:46:27 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_lexer_c(char c)
{
	if (c != ' ' && c != '<' && c != '>' && c != '|' && c != '"' && c != '\'')
		return (1);
	return (0);
}

char	*check_arg_dollar(t_lexer *lexer, char *str, char c)
{
	char	*tmp;
	t_token	*token;

	tmp = check_var(lexer);
	str = ft_h_strjoin(str, tmp);
	if (tmp[0] == '\0')
		free(tmp);
	if (c == '"')
		return (str);
	if (lexer->c == '"' || lexer->c == '\'')
	{
		c = lexer->c;
		token = lexer_collect_string(lexer);
		if (ft_free_token_and_string(token, str, 0))
			return (NULL);
		str = ft_h_strjoin(str, token->val);
		ft_free_token_and_string(token, str, 1);
		lexer->c = c;
	}
	else if (lexer->c == '/')
	{
		str = ft_h_strjoin(str, "/");
		lexer_advance(lexer);
	}
	return (str);
}

t_token	*ft_collect_string_second_2(t_lexer *lexer, t_token *token, char *str)
{
	lexer_advance(lexer);
	if (lexer->c && check_lexer_c(lexer->c))
	{
		token = lexer_collect_arg(lexer);
		if (ft_free_token_and_string(token, str, 0))
			return (init_token(t_error, NULL));
		str = ft_h_strjoin(str, token->val);
		ft_free_token_and_string(token, str, 1);
	}
	else if (lexer->c && (lexer->c == '\'' || lexer->c == '"'))
	{
		token = lexer_collect_string(lexer);
		if (ft_free_token_and_string(token, str, 0))
			return (init_token(t_error, NULL));
		str = ft_h_strjoin(str, token->val);
		ft_free_token_and_string(token, str, 1);
	}
	return (init_token(t_args, str));
}

char	*ft_lexer_collect_string_second_1(t_lexer *lexer, char *str, char c)
{
	char	*tmp;

	while (lexer->c && lexer->c != c)
	{
		if (c != '\'' && lexer->c == '$' && is_allnum(lexer->src[lexer->i + 1]))
			str = check_arg_dollar(lexer, str, c);
		else if (lexer->c == '$' && lexer->src[lexer->i + 1] == '\\')
			return (NULL);
		else
		{
			check_backslash(&lexer);
			tmp = lexer_get_current_char_as_string(lexer);
			str = ft_h_strjoin(str, tmp);
			free(tmp);
			lexer_advance(lexer);
		}
	}
	return (str);
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	t_token	*token;
	char	*str;
	char	c;

	c = lexer->c;
	lexer_advance(lexer);
	str = NULL;
	if (lexer->c == c && (lexer->src[lexer->i + 1] == '\0'
			|| lexer->src[lexer->i + 1] == ' '))
	{
		lexer_advance(lexer);
		return (init_token(t_args, ft_strdup("")));
	}
	str = ft_lexer_collect_string_second_1(lexer, str, c);
	if (!str)
		return (init_token(t_error, NULL));
	if (!lexer->c)
	{
		free(str);
		return (init_token(t_error, NULL));
	}
	return (ft_collect_string_second_2(lexer, token, str));
}
