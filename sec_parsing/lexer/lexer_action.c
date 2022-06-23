/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:41:04 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/19 19:41:06 by hjrifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->i < ft_strlen(lexer->src))
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

char	*check_var_second(t_lexer *lexer, char *str)
{
	char	*tmp;

	while (lexer->c != '\0' && lexer->c != '\\'
		&& lexer->c != ' ' && lexer->c != '$' && lexer->c != '|'
		&& lexer->c != '"' && lexer->c != '\'' && lexer->c != '='
		&& lexer->c != '/')
	{
		tmp = lexer_get_current_char_as_string(lexer);
		str = ft_h_strjoin(str, tmp);
		free(tmp);
		lexer_advance(lexer);
	}
	if (str && ft_getenv(lexer->mini, str))
	{
		tmp = ft_getenv(lexer->mini, str);
		free(str);
		return (tmp);
	}
	else
	{
		free(str);
		return (ft_strdup(""));
	}
	return (str);
}

char	*check_var(t_lexer *lexer)
{
	char	*str;

	str = NULL;
	lexer_advance(lexer);
	if (lexer->c == '\0' || lexer->c == ' ' || lexer->c == '"'
		|| lexer->c == '|' || lexer->c == '=' || lexer->c == '/')
		return (ft_strdup("$"));
	else if (lexer->c == '?')
	{
		lexer_advance(lexer);
		return (ft_itoa(g_status_exec));
	}
	else if ((lexer->c >= '0' && lexer->c <= '9') || lexer->c == '*')
	{
		lexer_advance(lexer);
		return (ft_strdup(""));
	}
	else if (lexer->c == '$')
	{
		lexer_advance(lexer);
		return (ft_itoa(getpid()));
	}
	else
		return (check_var_second(lexer, str));
	return (str);
}

void	check_backslash(t_lexer **lexer)
{
	char	c;
	char	k;

	c = (*lexer)->c;
	k = (*lexer)->src[(*lexer)->i + 1];
	if (c == '\\' && (k == '\\' || k == ';' || k == '"' || k == '\''
			|| k == '$' || k == '>' || k == '<'))
		lexer_advance(*lexer);
}
