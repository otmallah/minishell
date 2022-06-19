NAME = mini.a

CC = gcc 

FLAG = -Wall -Wextra -Werror 

HDR = 	header/minishell.h \
		header/utiles_functions.h

C_FILES =	functions/utiles_functions.c\
			exec/exec_cmd.c\
			exec/redirections.c\
			exec/pipes.c\
			built_func/cd.c\
			built_func/cd_utils.c\
			built_func/sec_utils_exp.c\
			built_func/echo.c\
			built_func/env.c\
			built_func/exit.c\
			built_func/export.c\
			built_func/pwd.c\
			built_func/unset.c\
			built_func/utils_exp.c\
			parser.c\
			utils/ft_split.c\
			utils/ft_strjoin.c\
			utils/ft_substr.c\
			utils/all_func.c\
			utils/ft_strcmp.c\
			utils/ft_itoa.c\
			utils/ft_calloc.c\
			exec/ft_getenv.c\
			exec/heredoc.c\
			exec/utils_pipes.c\
			mini.c\
			ft_error.c\
			get/get_next_line.c\
			exec/exit_status.c\
			exec/heredoc_utils.c\
			exec/sec_herdoc_utils.c\
			exec/sec_redirection_utils.c\
			exec/redirection_utils.c

OBJ = $(C_FILES:.c=.o)
# main.o\
# 		functions/utiles_functions.o\
# 		mini.o


all : $(NAME)

$(NAME) : $(HDR) $(OBJ) main.c
			$(CC)  -c $(C_FILES)
			ar -rc $(NAME) $(OBJ)
			$(CC) $(FLAG) -L /Users/otmallah/.brew/Cellar/readline/8.1.2/lib -I  /Users/otmallah/.brew/opt/readline/include -lreadline $(NAME) main.c  -o minishell

clean :	
		rm -f *.o functions/*.o
		rm -f *.o built_func/*.o
		rm -f *.o exec/*.o
		rm -f *.o utils/*.o
		rm -f $(NAME)
fclean : clean
		rm -f minishell
re : fclean all