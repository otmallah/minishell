
#include "../minishell.h"

int ft_print(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        printf("%s\n" , tab[i]);
        i++;
    }
}

void    ft_print_export(char **tab)
{
    int i;
    int a;
    char *temp = NULL;

    i = 0;
    //a = ft_tablen(tab);
    //printf("num = %d\n" , a);
    while (tab[i + 1] != NULL)
    {
        if (ft_strcmp(tab[i], tab[i + 1]) > 0)
        {
            temp = tab[i];
            tab[i] = tab[i + 1];
            tab[i + 1] = temp;
            i = -1;
        }
        i++;
    }
    ft_print(tab);
    free(tab);
    exit(0);
}

void    ft_export(t_mini *index, char *str)
{
    int i;
    int j;
    int asc;
    int a;
    char **tab_exp;

    i = 0;
    j = 0;
    asc = 65;
    while (index->string[i])
        i++;
    tab_exp = (char **)malloc(sizeof(char *) * i);
    i = 0;
    while (tab_exp[i])
    {
        while (index->string[j])
        {
            if (index->string[j][0] == (char)asc)
            {
                tab_exp[i] = index->string[j];
                i++;
            }
            j++;
        }
        if ((char)asc == 'Z')
            break ;
        asc++;
        j = 0;
    }
    tab_exp[i] = NULL;
    //printf("== %s\n" , tab_exp[i - 1]);
    ft_print_export(tab_exp);
}
