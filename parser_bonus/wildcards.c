/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otmallah <otmallah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:39 by otmallah          #+#    #+#             */
/*   Updated: 2022/06/22 21:27:42 by otmallah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void    ft_wildcars(t_shell *mini, char *str)
{
    int i;
    int j;
    int fd;
    int b = 0;
    char *temp;
    char *tab[FILENAME_MAX];
    char *sec_tab[] = {"ls", NULL};
    char    **spt;
    char *pok;
    int k;

    i = 0;
    j = 0;
    fd = open("/tmp/test", O_CREAT | O_RDWR , 0644);
    spt = ft_split(str, ' ');
    tab[j++] = spt[0];
    if (spt[1][0] == '*')
        b = 2;
    spt = ft_split(spt[1], '*');
    if (fork() == 0)
    {
        dup2(fd, 1);
        execve("/bin/ls", sec_tab, mini->tab_save_env);
    }
    wait(NULL);
    close(fd);
    fd = open("/tmp/test", O_CREAT | O_RDWR , 0644);
    if (spt[0] && spt[1])
    {
        char *pik;
        int o = 0;
        temp = get_next_line(fd);
        while (temp != NULL)
        {
            k = ft_strlen(spt[1]);
            pok = ft_strstr(temp, spt[1], k);
            k = ft_strlen(spt[0]);
            pik = ft_strstr2(temp, spt[0], k);
            if (pok && pik)
            {
                tab[j] = temp;
                j++;
            }
            temp = get_next_line(fd);
        }
    }
    else if (spt[0])
    {
        temp = get_next_line(fd);
        while (temp != NULL)
        {
            k = ft_strlen(spt[0]);
            if (b == 2)
                pok = ft_strstr(temp, spt[0], k);
            else if (b != 2)
                pok = ft_strstr2(temp, spt[0], k);
            if (pok)
            {
                tab[j] = temp;
                j++;
            }
            temp = get_next_line(fd);
        }
    }
    else if (spt[0] == NULL)
    {
        temp = get_next_line(fd);
        while (temp != NULL)
        {
            tab[j] = temp;
            j++;
            temp = get_next_line(fd);
        }
    }
    if (j == 1)
    {
        printf("minishell: no matches found: %s\n", spt[0]);
        g_status_exec = 127;
    }
    else
    {
        tab[j] = NULL;
        if (fork() == 0)
        {
            exec_cmd(mini, tab);
        }
        wait(NULL);
    }
    unlink("/tmp/test");
}