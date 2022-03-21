#include "../minishell.h"

#include "../minishell.h"

int ft_print(char *str, t_mini *index)
{
	int i;

	i = 0;
	while (index->tab_exp[i])
	{
		if (str == NULL)
			printf("%s\n" , index->tab_exp[i]);
		else
		{
			if (ft_strcmp(index->tab_exp[i], str) == 0 && index->finde == NULL)
				printf("%s=''\n", index->tab_exp[i]);
			else
				printf("%s\n" , index->tab_exp[i]);
		}
		i++;
	}
	return 0;
}

void    ft_print_export(char *str, t_mini *index)
{
	int i;
	int a;
	char *temp = NULL;

	i = 0;
	while (index->tab_exp[i + 1] != NULL)
	{
		if (ft_strcmp(index->tab_exp[i], index->tab_exp[i + 1]) > 0)
		{
			temp = index->tab_exp[i];
			index->tab_exp[i] = index->tab_exp[i + 1];
			index->tab_exp[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	ft_print(str, index);
	free(index->tab_exp);
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
			return(str);
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

	i = 0;
	j = 0;
	asc = 65;
	while (index->string[i])
		i++;
	if (str)
	{
		index->finde = find_value(str, index);
		index->count++;
	}
	index->tab_exp = (char **)malloc(sizeof(char *) * (i + index->count));
	i = 0;
	while (index->tab_exp[i])
	{
		while (index->string[j])
		{
			if (index->string[j][0] == (char)asc)
			{
				index->tab_exp[i] = index->string[j];
				i++;
			}
			j++;
		}
		if ((char)asc == 'Z')
		{
			if (index->count != 0) // bach n3raf bli rah dakhalt string
				index->tab_exp[i] = str;
			break ;
		}
		asc++;
		j = 0;
	}
	if (index->count == 0)
		index->tab_exp[i] = NULL; // ila makanch arg exp = export
	else
		index->tab_exp[i + 1] = NULL; //ila kant arg exist exp = export name=valuE
	ft_print_export(str, index);
}
