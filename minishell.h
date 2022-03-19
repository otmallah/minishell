#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 #include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_minishell
{
    char *str;
    char **string;
    char **tab;
}   t_mini;

char	**ft_split(const char *s, char l);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_pwd(void);
void    ft_cd(char *path);
char	*ft_strchr(const char *str, int c);
void    ft_exit(void);
void    ft_env(t_mini *index);
void	ft_echo(char *str);

// utils

int	ft_strcmp(char *s1, char *s2);