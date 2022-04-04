#all:
#	gcc main.c utils/ft_split.c utils/ft_substr.c utils/ft_strlen.c utils/ft_strjoin.c \
	builtin_func/ft_pwd.c builtin_func/ft_change_dir.c utils/ft_strchr.c \
	builtin_func/ft_exit.c builtin_func/env.c utils/ft_strcmp.c \
	builtin_func/ft_echo.c -o minishell -fsanitize=address
all :
	gcc  minishell.c utils/ft_split.c utils/ft_strcmp.c utils/ft_strlen.c utils/ft_strchr.c \
	utils/ft_strjoin.c utils/ft_substr.c builtin_func/ft_echo.c builtin_func/env.c \
	builtin_func/ft_change_dir.c link/ft_lstnew.c  link/ft_lstlast.c link/ft_lstadd_back.c \
	builtin_func/ft_pwd.c builtin_func/ft_export.c link/ft_lstadd_front.c utils/ft_strrchr.c \
	builtin_func/ft_unset.c builtin_func/ft_exit.c link/ft_lstclear.c builtin_func/utils_expo.c \
	builtin_func/utils_unset.c pipe2.c redirections.c \
	find_cmd_in_path.c -g -fsanitize=address  -lreadline -o minishell