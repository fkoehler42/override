/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incudes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wandre <wandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 13:57:32 by wandre            #+#    #+#             */
/*   Updated: 2016/01/07 10:24:56 by wandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define deathrays \
    __asm__ volatile("push     %eax      \n"\
                     "xor      %eax, %eax\n"\
                     "jz       .+5       \n"\
                     ".word    0xC483    \n"\
                     ".byte    0x04      \n"\
                     "pop      %eax      \n");

#define clear_argv(_argv) \
		for (; *_argv; ++_argv) { \
			memset(*_argv, 0, strlen(*_argv)); \
		}

#define clear_envp(_envp) clear_argv(_envp)

#define disable_buffering(_fd) setvbuf(_fd, NULL,  _IONBF, 0)

void 	
clear_stdin(void)
{
	char x = 0;
	while (42)
	{
		x = getchar();
		if (x == '\n' || x == EOF)	
			break;
	}
}

unsigned int 
get_unum(void)
{
	unsigned int res = 0;
	fflush(stdout);
	scanf("%u", &res);
	clear_stdin();
	return res;
}

void 
prog_timeout(int sig)
{
	(void)sig;
	asm("mov $1, %eax;"
		"mov $1, %ebx;"
		"int $0x80");
}

#include <signal.h>
#define ENABLE_TIMEOUT(_time)\
	__attribute__ ((constructor)) \
	void enable_timeout_cons() \
	{\
		signal(SIGALRM, prog_timeout); \
		alarm(_time); \
	}

#define ANSI_COLOR_RED 		"\x1b[31m"
#define ANSI_COLOR_GREEN 	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[33m"
#define ANSI_COLOR_RESET	"\x1b[0m"
