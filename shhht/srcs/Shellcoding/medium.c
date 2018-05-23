#include <signal.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/prctl.h>
#include <wait.h>
#include "../../includes/utils.h"

ENABLE_TIMEOUT(60)

/* 
   gcc -I../../includes/ -m32 -z execstack -fno-stack-protector -o medium medium.c 
*/


int main(void) {
	pid_t child = fork();
	char buffer[128] = {0};
	int syscall = 0;
	int status = 0;

	if(child == 0) {
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);

		puts("Give me some shellcode, k");
		gets(buffer);
	} else {
		while(1) {
			wait(&status);
			if (WIFEXITED(status) || WIFSIGNALED(status)){
				puts("child is exiting...");
				break;
			}

			syscall = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);

			if(syscall == 11) {
				printf("no exec() for you\n");
				kill(child, SIGKILL);
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}
