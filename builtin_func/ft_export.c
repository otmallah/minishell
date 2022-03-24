#include "../minishell.h"

int	find_value(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return 1;
		i++;
	}
	return 0;
}

void	ft_print_temp(char **tab, t_idx *id)
{
	int i;
	int a;

	i = 0;
	while (i <= id->d)
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

void	add_to_temp2(t_mini *index, t_idx *id)
{
	int i;
	int j;
	char **temp;

	i = id->d;
	j = 0;
	temp = (char **)malloc(sizeof(char *) * id->c);
	while (i >= 0)
	{
		temp[j] = index->tab_e[j];
		j++;
		i--;
	}
	index->tab_e = (char **)malloc(sizeof(char *) * id->c);
	j = 0;
	i = id->d;
	while (i >= 0)
	{
		index->tab_e[j] = temp[j];
		j++;
		i--;
	}
}

int find_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return i;
		i++;
	}
	return 0;
}

int	find_duplicate(t_mini *index, char *str,t_idx *id)
{
	int i;
	int j;
	int a;
	int res;
	char *temp;
	char *find;

	i = id->d;
	a = 0;
	j = 0;
	while (i >= 0)
	{
		a = find_value(str);
		if (a == 1)
		{
			temp= ft_substr(str, 0, find_len(str));
			if (ft_strcmp(ft_substr(index->tab_e[j], 0, find_len(index->tab_e[j])), temp) == 0)
			{
				index->tab_e[j] = str;
				return 1;
			}
		}
		if (ft_strcmp(index->tab_e[j], str) == 0)
		{
			return 1;
		}
		i--;
		j++;
	}
	return 0;
}

void	ft_print(t_mini *index, char *str, t_idx *id)
{
	int i;
	int j;
	int a = 0;
	char **temp;
	char *str_2;

	i = 0;
	j = 0;
	while (index->tab_exp[i])
	{
		if (str)
		{
			str_2 = ft_substr(index->tab_exp[i], 0, find_len(index->tab_exp[i]));
			if (ft_strcmp(str, str_2) == 0)
				a = 2;
		}
		printf("declare -x %s\n" , index->tab_exp[i]);
		i++;
	}
	if (str != NULL && a != 2)
	{
		id->c++;
		if (!index->tab_e)
		{
			index->tab_e = (char **)malloc(sizeof(char *) * id->c);
			index->tab_e[id->d] = str;
		}
		else
		{
			j = find_duplicate(index, str, id);
			//printf("j == %d\n", j);
			if (j == 0)
			{
				add_to_temp2(index, id);
				id->d++;
				index->tab_e[id->d] = str;
			}
		}
	}
	if (index->tab_e)
		ft_print_temp(index->tab_e, id);
}

void    ft_print_export(char *str, t_mini *index, t_idx *id)
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
	ft_print(index, str, id);
}


void	ft_export(t_mini *index, t_idx *id, char *str)
{
	if (str)
	{
		id->cnt = find_value(str);
		if (id->cnt == 1)
			index->finde = str;
		index->count++;
	}
	ft_print_export(str, index, id);
}
