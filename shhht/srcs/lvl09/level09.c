/*
   gcc -pie -fPIE -fno-stack-protector -o level9 level9.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct savestate {
	char tweet[140];
	char username[40];
	int msglen;
} save;

void set_msg(struct savestate *save );
void set_username(struct savestate * save);

void secret_backdoor(void) {
	char cmd[128];

	fgets(cmd, 128, stdin);
	system(cmd);

	return;
}

void handle_msg(void) {
	struct savestate save;

	memset(save.username, 0, 40);
	save.msglen = 140;

	set_username(&save);
	set_msg(&save);

	printf(">: Msg sent!\n");
	return;
}

void set_msg(struct savestate *save) {
	char readbuf[1024];
	memset(readbuf, 0, 1024);

	printf(">: Msg @Unix-Dude\n");
	printf(">>: ");
	fgets(readbuf, 1024, stdin);
	strncpy(save->tweet, readbuf, save->msglen);

	return;
}

void set_username(struct savestate * save) {
	int i;
	char readbuf[128];
	memset(readbuf, 0, 128);

	printf(">: Enter your username\n");
	printf(">>: ");

	fgets(readbuf, 128, stdin);
	for(i = 0; i <= 40 && readbuf[i]; i++)
		save->username[i] = readbuf[i];

	printf(">: Welcome, %s", save->username);
	return;
}

int main(void)
{

	printf(
			"--------------------------------------------\n" \
			"|   ~Welcome to l33t-m$n ~    v1337        |\n" \
			"--------------------------------------------\n");

	handle_msg();

	return EXIT_SUCCESS;
}
