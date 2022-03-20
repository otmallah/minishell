#include "../minishell.h"

int ft_print(char **tab, char *str, t_mini *index)
{
    int i;

    i = 0;
    while (tab[i])
    {
        if (str == NULL)
            printf("%s\n" , tab[i]);
        else
        {
            if (ft_strcmp(tab[i], str) == 0 && index->finde == NULL)
                printf("%s=''\n", tab[i]);
            else
                printf("%s\n" , tab[i]);
        }
        i++;
    }
}

void    ft_print_export(char **tab, char *str, t_mini *index)
{
    int i;
    int a;
    char *temp = NULL;

    i = 0;
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
    ft_print(tab, str, index);
    free(tab);
    exit(0);
}

char    *find_value(char *str, t_mini *index)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
        {
            i++;
            return(str + i);
        }
        i++;
    }
    return NULL;
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
    a = 0;
    asc = 65;
    while (index->string[i])
        i++;
    if (str)
    {
        index->finde = find_value(str, index);
        a++;
    }
    else
        str = NULL;
    tab_exp = (char **)malloc(sizeof(char *) * (i + a));
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
        {
            if (a != 0) // bach n3raf bli rah dakhalt string
                tab_exp[i] = str;
            break ;
        }
        asc++;
        j = 0;
    }
    if (a == 0)
        tab_exp[i] = NULL; // ila makanch arg exp= expor
    else
        tab_exp[i + 1] = NULL; //ila kant arg exist exp = export name=value
    ft_print_export(tab_exp, str, index);
}
