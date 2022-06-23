/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:47:39 by hjrifi            #+#    #+#             */
/*   Updated: 2022/06/20 22:28:35 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utiles_functions.h"
# include "../../shell.h"

typedef struct t_lexer
{
	char			c;
	unsigned int	i;
	char			*src;
	t_shell			*mini;
}	t_lexer;

typedef struct token_struct
{
	enum {
		t_command = 1,
		t_args = 2,
		t_heredoc = 3,
		t_append = 4,
		t_file = 5,
		t_output = 8,
		t_end = 7,
		t_input = 6,
		t_l_parenthesis = 9,
		t_r_parenthesis = 10,
		t_pip = 11,
		t_or = 12,
		t_and = 13,
		t_error = 14,
	}	e_type;
	char	*val;
}	t_token;

char	*get_next_line(int fd);
void	ft_mini(t_shell *mini, char *src);
t_lexer	*init_lexer(char *src, t_shell *mini);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
void	lixer_skip_whitespace(t_lexer *lexer);
t_token	*lexer_get_next_token(t_lexer *lexer, t_token *token);
t_token	*lexer_collect_string(t_lexer *lexer);
t_token	*lexer_collect_arg(t_lexer *lexer);
char	*check_var(t_lexer *lexer);
char	*lexer_get_current_char_as_string(t_lexer *lexer);
t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);
t_token	*init_token(int t_type, char *val);
int		is_allnum(char c);
char	*check_arg_dollar(t_lexer *lexer, char *str, char c);
void	check_backslash(t_lexer **lexer);
t_list	*ft_parser(char *src, t_shell *mini);
t_list	*print_error(char *str, t_lexer *lexer, t_token *token, t_list *lst);
char	*ft_getenv(t_shell *mini, char *str);
int		ft_free_token_and_string(t_token *token, char *str, int n);
t_list	*add_node_in_lst(char *str, int v_type, t_list *lst);
int		ft_error(t_lexer *lexer);
#endif
