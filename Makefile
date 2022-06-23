NAME = mini.a

CC = gcc 

FLAG = -Wall -Wextra -Werror 

HDR = 	sec_parsing/header/minishell.h\
		sec_parsing/header/utiles_functions.h

C_FILES =	exec/exec_cmd.c\
			exec/redirections.c\
			exec/pipes.c\
			exec/utils_exec_cmd.c\
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
			exec/exit_status.c\
			exec/heredoc_utils.c\
			exec/sec_herdoc_utils.c\
			exec/sec_redirection_utils.c\
			exec/redirection_utils.c\
			sec_parsing/functions/utiles_functions.c\
			sec_parsing/functions/ft_error.c\
			sec_parsing/parsing/parser.c\
			sec_parsing/parsing/parser_second.c\
			sec_parsing/ft_free/ft_free_list.c\
			sec_parsing/lexer/mini.c\
			sec_parsing/lexer/lexer_action.c\
			sec_parsing/lexer/lexer.c\
			sec_parsing/lexer/token.c\
			get/get_next_line.c\
			ft_strstr.c\
			ft_wildcards.c

OBJ = $(C_FILES:.c=.o)
# main.o\
# 		functions/utiles_functions.o\
# 		mini.o


all : $(NAME)

$(NAME) : $(HDR) $(OBJ) main.c
			$(CC)  -c $(C_FILES)
			ar -rc $(NAME) $(OBJ)
			$(CC) $(FLAG) -L /Users/otmallah/.brew/Cellar/readline/8.1.2/lib -I  /Users/otmallah/.brew/opt/readline/include -lreadline $(NAME) main.c  -o minishell -fsanitize=address -g
clean :	
		rm -f *.o sec_parsing/functions/*.o
		rm -f *.o sec_parsing/ft_free/*.o
		rm -f *.o built_func/*.o
		rm -f *.o exec/*.o
		rm -f *.o utils/*.o
		rm -f *.o sec_parsing/parsing/*.o
		rm -f *.o sec_parsing/lexer/*.o
		rm -f $(NAME)
fclean : clean
		rm -f minishell
re : fclean all