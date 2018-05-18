#include <unistd.h>
#include <signal.h>

int         main(int argc, char **argv)
{
    int     pid = fork();
    char    str[32];
    memset(str, '\0', 32);
    if (pid == 0)
    {
        puts("Give me some shellcode, k");
    }
    else
    {
        puts("no exec() for you");
        kill(pid, SIGKILL);
    }
    return (0);
}