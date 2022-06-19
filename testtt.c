#include<stdio.h>
#include<signal.h>
#include<unistd.h>
//signal handling function that will except ctrl-\ and ctrl-c
void sig_handler(int signo)
{
    //looks for ctrl-c which has a value of 2
    if (signo == SIGINT)
        printf("\nreceived SIGINT\n");
    //looks for ctrl-\ which has a value of 9
    else if (signo == SIGQUIT)
        printf("\nreceived SIGQUIT\n");
}

int main(void)
{
    //these if statement catch errors
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    if (signal(SIGQUIT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGQUIT\n");
    //Runs the program infinitely so we can continue to input signals
    while(1)
        sleep(1);
    return 0;
}
