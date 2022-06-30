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
			built_func/unset_second.c\
			built_func/utils_exp.c\
			built_func/sec_sec_exp.c\
			utils/ft_split.c\
			utils/ft_strjoin.c\
			utils/ft_substr.c\
			utils/ft_atoi.c\
			utils/all_func.c\
			utils/ft_strcmp.c\
			utils/ft_itoa.c\
			utils/ft_calloc.c\
			exec/ft_getenv.c\
			exec/heredoc.c\
			exec/utils_pipes.c\
			exec/utils_check.c\
			exec/exit_status.c\
			exec/heredoc_utils.c\
			exec/sec_herdoc_utils.c\
			exec/sec_redirection_utils.c\
			exec/norme.c\
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
			check_if_herdoc/check_if_herdoc.c

OBJ = $(C_FILES:.c=.o)

all : $(NAME)

$(NAME) : $(HDR) $(OBJ) main.c
			$(CC) $(FLAG) -c $(C_FILES)
			ar -rc $(NAME) $(OBJ)
			$(CC) $(FLAG) -L /Users/otmallah/.brew/Cellar/readline/8.1.2/lib -I /Users/otmallah/.brew/opt/readline/include -lreadline $(NAME) main.c -o minishell
clean :	
		rm -f *.o sec_parsing/functions/*.o
		rm -f *.o sec_parsing/ft_free/*.o
		rm -f *.o built_func/*.o
		rm -f *.o exec/*.o
		rm -f *.o utils/*.o
		rm -f *.o sec_parsing/parsing/*.o
		rm -f *.o sec_parsing/lexer/*.o
		rm -f *.o bonus_minishell/sec_parsing/functions/*.o
		rm -f *.o bonus_minishell/sec_parsing/ft_free/*.o
		rm -f *.o bonus_minishell/built_func/*.o
		rm -f *.o bonus_minishell/exec/*.o
		rm -f *.o bonus_minishell/utils/*.o
		rm -f *.o bonus_minishell/sec_parsing/parsing/*.o
		rm -f *.o bonus_minishell/sec_parsing/lexer/*.o
		rm -f *.o bonus_minishell/get/*.o
		rm -f *.o bonus_minishell/ft_and_or/*.o
		rm -f *.o bonus_minishell/exec_bonus/*.o
		rm -f *.o bonus_minishell/*.o
		rm -f *.o check_if_herdoc/*.o
		rm -f $(NAME)
		rm -f $(BONUS_NAME)
fclean : clean
		rm -f minishell minishell_bonus
re : fclean all

################################ BONUS ###########################################
BONUS_NAME = bonus_mini.a

BNS_FILES = bonus_minishell/exec/exec_cmd.c\
			bonus_minishell/exec/redirections.c\
			bonus_minishell/exec/pipes.c\
			bonus_minishell/exec/utils_exec_cmd.c\
			bonus_minishell/built_func/cd.c\
			bonus_minishell/built_func/cd_utils.c\
			bonus_minishell/built_func/sec_utils_exp.c\
			bonus_minishell/built_func/echo.c\
			bonus_minishell/built_func/env.c\
			bonus_minishell/built_func/exit.c\
			bonus_minishell/built_func/export.c\
			bonus_minishell/built_func/pwd.c\
			bonus_minishell/built_func/unset.c\
			bonus_minishell/built_func/utils_exp.c\
			bonus_minishell/built_func/sec_sec_exp.c\
			bonus_minishell/utils/ft_split.c\
			bonus_minishell/utils/ft_strjoin.c\
			bonus_minishell/utils/ft_substr.c\
			bonus_minishell/built_func/unset_second.c\
			bonus_minishell/utils/all_func.c\
			bonus_minishell/utils/ft_strcmp.c\
			bonus_minishell/utils/ft_itoa.c\
			bonus_minishell/utils/ft_atoi.c\
			bonus_minishell/utils/ft_calloc.c\
			bonus_minishell/exec/utils_check.c\
			bonus_minishell/exec/ft_getenv.c\
			bonus_minishell/exec/heredoc.c\
			bonus_minishell/exec/utils_pipes.c\
			bonus_minishell/exec/exit_status.c\
			bonus_minishell/exec/heredoc_utils.c\
			bonus_minishell/exec/sec_herdoc_utils.c\
			bonus_minishell/exec/sec_redirection_utils.c\
			bonus_minishell/exec/norme.c\
			bonus_minishell/exec/redirection_utils.c\
			bonus_minishell/exec_bonus/wildcards.c\
			bonus_minishell/exec_bonus/utils_wildcards.c\
			bonus_minishell/exec_bonus/ft_and_or.c\
			bonus_minishell/exec_bonus/sec_utils_wild.c\
			bonus_minishell/get/get_next_line.c\
			bonus_minishell/sec_parsing/functions/utiles_functions.c\
			bonus_minishell/sec_parsing/functions/ft_error.c\
			bonus_minishell/sec_parsing/parsing/parser.c\
			bonus_minishell/sec_parsing/parsing/parser_second.c\
			bonus_minishell/sec_parsing/ft_free/ft_free_list.c\
			bonus_minishell/sec_parsing/lexer/mini.c\
			bonus_minishell/sec_parsing/lexer/lexer_action.c\
			bonus_minishell/sec_parsing/lexer/lexer.c\
			bonus_minishell/sec_parsing/lexer/token.c\
			bonus_minishell/sec_parsing/parsing/parenthesis.c\
			bonus_minishell/sec_parsing/functions/check_string_cmd.c\
			bonus_minishell/ft_strstr.c


BNS_OBJ = $(BNS_FILES:.c=.o)

bonus : $(BONUS_NAME)

$(BONUS_NAME) :  $(BNS_OBJ) bonus_minishell/main.c
			$(CC) $(FLAG) -c $(BNS_FILES)
			ar -rc $(BONUS_NAME) $(BNS_OBJ)
			$(CC) $(FLAG) -L /Users/otmallah/.brew/Cellar/readline/8.1.2/lib -I /Users/otmallah/.brew/opt/readline/include -lreadline $(BONUS_NAME) bonus_minishell/main.c -o minishell_bonus 
