


#include <fcntl.h>
#include <stdio.h>
#include "shell.h"

int main(int ac, char **av, char **env)
{
    int fd[2];
    int temp_fd;
    int n_fd;
    char *tab[] = {"ls", NULL};
    char *tab2[] = {"wc", NULL};
    int i = 0;
    int save[10];
    while (i < 2)
    {
        if (pipe(fd))
            perror(NULL);
        int id = fork();
        if (id == 0)
        {
            if (i == 0)
            {
                close(fd[0]);
                dup2(fd[1], 1);
                execve("/bin/ls", tab, env);
            }
            else
            {
                dup2(temp_fd, 0);
                execve("/usr/bin/wc", tab, env);
            }
            exit(0);
        }
        save[i] = id;
        i++;
        temp_fd = dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
    }
    if (i-- > 0)
        waitpid(save[i], 0 ,0);
}