/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 20:46:41 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/24 10:33:05 by otmallah         ###   ########.fr       */
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

typedef struct s_ids
{
	unsigned int	g_status_exec;
	int				id;
	int				cheecker;
	int				g_fd;
	int				failer;
}	t_ids;

t_ids	g_id;

typedef struct s_shell {
	char	**tab_save_exp;
	char	**tab_save_env;
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
	int	global_fd_out;
	int	global_fd_in;
	int	global_fd;
}	t_global;

typedef struct t_list
{
	char			**val;
	int				*v_type;
	struct t_list	*next;
	struct t_list	*prev;
}	t_list;

typedef struct s_wild
{
	char	*get_next;
	char	*str1;
	char	*str2;
	char	**tab_wild;
	int		size;
	int		out_file;
	int		in_file;
	int		size_j;
}	t_wild;

int		ft_atoi(const char *str);
void	add_name2(int i, char *str);
void	err_wild(char *str);
void	mult_wild(t_list **list, t_wild *wild, char **tab, int fd);
void	exec_both_and_or(t_list *list, t_shell *mini);
void	ft_or(t_list **list, t_shell *mini);
void	ft_and(t_list **list, t_shell *mini);
void	handler(int sig);
void	ft_free(char **tab);
char	*utils_path_if_exi(t_shell *mini);
char	*ft_getenv_utils(t_shell *m, char *str);
int		size_vl(char **str);
void	cmm(t_list *lst, t_shell *mini);
void	cmm_exit(t_list *lst, int fd);
void	cmm_cd(t_list *lst, t_shell *mini);
void	built_sec(t_shell *mini, t_list *lst, int fd);
int		utils_redin(t_list *lst);
void	change_in(t_list **lst, t_shell *mini);
int		utils_re(t_list *lst, int fd_in, int k);
char	**cmd_utils(t_list *list, char **tab);
char	**cmd(t_list *list);
void	utils_red(t_list **lst);
int		utils_files(t_list *list, int a, int fd, int fd_in);
void	ex(t_shell *mini, t_list *list, int *save, int fs);
int		size_tab(char **tab);
void	ft_nor(t_shell *mini, int fd, int fd_out, int fd_in);
int		ft_index(t_list *list);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *src);
char	**ft_split(char *s, char l);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *s,	int fd);
char	*ft_itoa(int n);
void	*ft_calloc(size_t n, size_t c);
char	*ft_strstr(char *str, char *to_find, int size);
char	*ft_strstr2(char *str, char *to_find, int size);
int		ft_isdigit(int c);
int		find(char *str);
int		ft_strcmp(char *s1, char *s2);
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
void	ft_echo(char **str, int fd);
void	ft_check_built(t_shell *mini, t_list *lst, int fd);
void	ft_redirection(t_shell *mini, t_list *lst, int a, int tem_fd);
int		finder(char *str);
int		invalide_identifier(char *str, int fd);
void	heredoc(t_shell *mini, t_list *list, int num, int fd_out);
int		open_all_files(t_list *list, int a);
void	red_in(t_shell *mini, char *str);
int		search_path_in_env(t_shell *mini, int a);
void	ft_redin(t_shell *mini, t_list *lst, int te_fd, int num);
void	change(t_list **list, t_wild *wild);
int		sec_utils_wild(t_wild *wild, int i, int count, char **tab);
void	utils_milt_wild(t_wild *wild, char **tab, int fd);
void	utils_mult_wild(t_list **list, t_wild *wild, char *tab, int fd);
void	mult_wild(t_list **list, t_wild *wild, char **tab, int fd);
void	one_wild(t_wild *wild, int fd);
void	import_all_arg(t_list **list, t_wild *wild, int fd);
void	exec_wild(t_shell *mini, t_list **list);
void	utils_exec_wild(t_wild *wild, t_shell *mini, t_list **list, int fd_out);
void	ft_wildcards(t_list **list, t_shell *mini, int fd_out);
char	*get_next_line(int fd);
char	*ft_strstr(char *str, char *to_find, int size);
char	*ft_strstr3(char *str, char *to_find, int size);
char	*ft_strstr2(char *str, char *to_find, int size);
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
int		find_both_and_or(t_list *list);
int		ft_findwild(t_list *list);
int		finde_her(t_list *lis);
void	ft_mini_second(t_shell *mini, t_list *lst);
void	ft_copy_tab_save_env(t_shell *index, char **temp, int n, int j);
void	ft_check_cmd_if_exists(t_shell *mini, t_list *lst, DIR *dp);
int		ft_free_and_dup_val(t_list **list, char **sec_tab, int io);
int		ft_free_lst_val(t_list **lst, int ij);
int		ft_check_cmd_out(t_list *list);

#endif