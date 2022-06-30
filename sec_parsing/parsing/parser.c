/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjrifi <hjrifi@student.42.fr>          	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:12 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/14 17:34:31 by hjrifi	          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_list	*ft_check_parser(t_token **token, t_lexer *lexer,
t_list *lst)
{
	int	i;

	i = 1;
	*token = lexer_get_next_token(lexer, *token);
	while (*token && (*token)->e_type == t_args)
	{
		lst->val = ft_realloc_char(lst->val);
		lst->v_type = ft_realloc_int(lst->v_type, lst->val);
		lst->val[i] = ft_strdup((*token)->val);
		lst->v_type[i++] = (*token)->e_type;
		free((*token)->val);
		*token = lexer_get_next_token(lexer, *token);
	}
	if (i > 1 && lst->v_type[0] == 3)
		lst->v_type[1] = t_end;
	else if (i > 1 && lst->v_type[0] == t_output)
		lst->v_type[1] = t_file;
	if ((*token) && (*token)->e_type == t_error)
		return (NULL);
	return (lst);
}

int	is_string_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

t_list	*ft_parser_second(t_lexer *lexer, t_token *token,
t_list *lst, t_list *head)
{
	while (token && token->e_type != t_error)
	{
		lst = ft_check_parser(&token, lexer, lst);
		if (!lst)
			return (print_error(" 003", lexer, token, head));
		if (token && lst)
		{
			lst = add_node_in_lst(token->val, token->e_type, head);
			if (!lst)
				return (print_error(" 001", lexer, token, head));
			if (token->e_type > t_output && token->e_type <= t_error)
			{
				token = lexer_get_next_token(lexer, token);
				lst = add_node_in_lst(token->val, token->e_type, head);
				if (!lst || token->e_type == t_error)
					return (print_error(" 002", lexer, token, head));
			}
			while (lst->next)
				lst = lst->next;
		}
	}
	return (head);
}

t_list	*ft_parser(char *src, t_shell *mini)
{
	t_lexer	*lexer;
	t_token	*token;
	t_list	*lst;
	t_list	*head;

	token = NULL;
	lst = NULL;
	if (is_string_empty(src))
		return (NULL);
	lexer = init_lexer(src, mini);
	token = lexer_get_next_token(lexer, token);
	if (token)
		lst = add_node_in_lst(token->val, token->e_type, lst);
	if (token && token->e_type == t_error)
		return (print_error(" 000", lexer, token, lst));
	head = lst;
	lst = ft_parser_second(lexer, token, lst, head);
	if (!lst)
		return (NULL);
	free(lexer);
	return (head);
}
