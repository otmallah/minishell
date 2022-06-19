/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:46:41 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/19 19:02:49 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>

#define	TEST_HACK1	ft_strcmp(list->val[0], "cat") == 0
#define	TEST_HACK2	ft_strcmp(list->val[0], "wc") == 0
#define	TEST_HACK3	ft_strcmp(list->val[0], "grep") == 0 
#define	TEST_HACK4	ft_strcmp(list->val[0], "more") == 0   

unsigned int	g_status_exec;
int id;

typedef struct s_shell {
	char	**tab_save_env;
	char	**tab_save_exp;
	char	*save_pwd;
	char	*save_old_pwd;
	int		counter;
	int		num_ofall_cmd;
	int		built;
	int		temp_fd;
	int		num_cmd;
	int		*save;
	int		id;
	int		cnt;
	int		fs;
	int		num_of_fd;
	char	**tab_of_norm;
}	t_shell;

typedef struct s_global
{
	int	global_id;
}	t_global;


typedef struct t_list
{
	char			**val;
	int				*v_type;
	struct t_list	*next;
	struct t_list	*prev;
}	t_list;

int		utils_redin(t_list *lst);
void	change_in(t_list **lst);
int		utils_re(t_list *lst, int fd_in, int k);
char	**cmd_utils(t_list *list, char **tab);
char	**cmd(t_list *list);
void	utils_red(t_list **lst, t_shell *mini);
int		utils_files(t_list *list, int a, int fd, int fd_in);
void	ex(t_shell *mini, t_list *list, int *save, int fs);
int		size_tab(char **tab);
void	ft_nor(t_shell *mini, int fd, int fd_out);
int	ft_index(t_list *list);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *src);
char	**ft_split(char *s, char l);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s,	int fd);
//char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
void	*ft_calloc(size_t n, size_t c);
//char	*get_next_line(int fd);
char	*ft_strstr(char *str, char *to_find, int size);
char	*ft_strstr2(char *str, char *to_find, int size);
int		ft_isdigit(int c);
int		find(char *str);
int		ft_strcmp(char *s1, char *s2);
//int		ft_isdigit(int c);
void	change_pwd(t_shell *mini);
int		search_path_in_env(t_shell *mini, int a);
int		go_home(t_shell *mini);
void	unset_home(t_shell *mini);
void	norme(t_shell *index);
int		norme2(t_shell *index, char *str, char **temp, char **sec_temp);
void	oldpwd_not_set(t_shell *mini);
int		loop(t_shell *mini);
void	ft_13(t_shell *index, char *str, char **save, char **temp);
void	norme4(t_shell *index, char **temp, char *str, char **save);
void	unset_exp(t_shell *index, char *str);
void	ft_execve(char **temp, t_shell *mini, t_list *lst);
void	ft_err(char *str);
int		no(t_shell *index, char *add_str, char *string, int i);
int		no1(t_shell *index, char *add_str, char *string, int i);
void	exec_first_cmd(t_list *list, t_shell *mini, int *fd);
void	exec_last_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd);
void	exec_sec_cmd(t_list *list, t_shell *mini, int temp_fd, int *fd);
void	normm(t_list *list, t_shell *mini, int *fd, int i);
int		nomm1(t_list **list, t_shell *mini, int *fd, int i);
int		fin(t_list *list);
void	simple_cmd(t_shell *mini, t_list *list, int i, int *fd);
void	exec_first_cmd_in_her(t_list *list, t_shell *mini, int fd_out, int num);
char	**save_dele(t_list *list);
void	norme_first_cmd(t_list **list, t_shell *mini);
char	**save_cmd(t_list *list);
void	norm_exec_her(t_shell *mini, t_list **list);


int		check_herd(t_shell *mini, t_list *list);
void	pipes(t_shell *mini, t_list *list);
int		len(char *str);
void	ft_print(t_shell *index, int fd);
void	ft_realloc(t_shell *index, char *str, int save);
int		duplicate_exp(t_shell *index, char *string, char *add_str, int i);
void	ft_print_export(t_shell *index, char **str, int fd);
int		add_str_tab_exp(t_shell *index, char *str);
int		check_duplicate(t_shell *index, char *str);
void	exec_cmd(t_shell *mini, t_list *lst);
void	ft_check_cmd(t_shell *mini, t_list *list);
char	*check_path_if_exi(t_shell *mini);
void	ft_echo(t_shell *mini, char **str, int fd);
void	ft_check_built(t_shell *mini, t_list *lst, int fd);
void	ft_redirection(t_shell *mini, t_list *lst, int a, int tem_fd);
int		finder(char *str);
int		invalide_identifier(char *str, int fd);
void	heredoc(t_shell *mini, t_list *list, int num, int fd_out);
int		open_all_files(t_list *list, int a);
void	red_in(t_shell *mini, char *str);
//int		ft_and_bonus(t_shell *mini, char *str);
//void	ft_or_bonus(t_shell *mini, char *str);
int		search_path_in_env(t_shell *mini, int a);
//int		find_both(char *str);
//void	ft_both(t_shell *mini, char *str);
//void	ft_wildcars(t_shell *mini, char *str);
void	ft_redin(t_shell *mini, t_list *lst, int te_fd, int num);

// exit

void	ft_exit(char **str, int fd, int num);
void	ft_env(t_shell *index, int fd);
void	ft_unset(t_shell *index, char **str, int fd);
void	ft_cd(char *path, t_shell *mini);
void	ft_pwd(int fd);
int		tablen(char **tab);
int		ft_pipe(t_shell *mini, char *str);
char	**save_cmd(t_list *list);
int		fd_i(t_list *list);
void	ft_exit_status(t_shell *mini, t_list *lst);
#endif