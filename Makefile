all:
	gcc main.c utils/ft_split.c utils/ft_substr.c utils/ft_strlen.c utils/ft_strjoin.c \
	builtin_func/ft_pwd.c builtin_func/ft_change_dir.c utils/ft_strchr.c \
	builtin_func/ft_exit.c -o minishell -fsanitize=address