#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int			main(int argc, char **argv) {
	char	buf_file[42];
	FILE	*fs;
	size_t	nbytes;
	char	buf_user[100];
	char	buf_pass[100];

	fs = fopen("/home/users/level03/.pass", "r");
	if (fs == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}

	nbytes = fread(buf_file, 1, 41, fs);
	*(buf_file + strcspn(buf_file, "\n")) = '\0';

	if (nbytes != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}

	fclose(fs);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	
	printf("--[ Username:");
	*(buf_user + strcspn(buf_user, "\n")) = '\0';
	printf("--[ Password:");
	*(buf_pass + strcspn(buf_pass, "\n")) = '\0';
	puts("*****************************************");

	if (strncmp(buf_file, buf_pass, 41) == 0) {
		printf("Greetings, %s!\n", buf_user);
		system("/bin/sh");
		return (0);
	}
	printf(buf_user);
	puts(" does not have access!");
	exit(1);
}