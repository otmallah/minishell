#include "minishell.h"

int main ()
{
    const char *str;

        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
}