#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <sys/prctl.h>

int         main(int argc, char **argv)
{
    int     pid = fork();
    char    str[32];
    int     stat_loc = 0;

    memset(str, '\0', 32);
    if (pid == 0)
    {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        puts("Give me some shellcode, k");
        gets(str);
    }
    else
    {
        while (true) {
            wait(&stat_loc);
            if ((stat_loc & 0x7f) != 0) {
                if (WIFEXITED(stat_loc) > 0) {
                    puts("child is exiting...");
                    return (0);
                }
            }
            if (ptrace(PTRACE_PEEKUSER, pid, 0x2c, NULL) == 11) // exec syscall
                break ;
        }
        puts("no exec() for you");
        kill(pid, SIGKILL);
    }
    return (0);
}