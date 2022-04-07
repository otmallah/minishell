#include "minishell.h"

int main (int ac, char **av)
{
	int fd;
	int i = 0;
	char *str;

	if (access("texxt" , F_OK) == 0)
	{
		int fd = fileno("texxt");
		i = 1;
	}
	else
		fd = open("texxt", O_CREAT | O_RDWR , 0644);
	while (1)
	{
		str = readline("");
		if (strcmp(str, "ls") == 0)
			exit(0);
		else
		{
			write (fd, str, strlen(str));
			write (fd, "\n", 1);
		}
		i++;
	}
}