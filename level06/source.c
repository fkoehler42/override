#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int     auth(char *login, unsigned int serial) {
    int     len;
    int     check;
    int     i;


    *(login + strcspn(login, "\n")) = '\0';
    len = strnlen(login, 32);
    if (len <= 5)
        return (1);
    if (ptrace(0, 0, 1, NULL) == -1) {
        puts("\033[32m.---------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !!  |");
        puts("\033[32m'---------------------------'");
        return (1);
    }
    check = login[3] ^ 4919 + 6221293;
    i = 0;
    while (i < len) {
        if (login[i] <= 31)
            return (1);
        int check2 = login[i] ^ check;
        int check3 = (int)((int64_t)0x88233b2b * check2 / 0x100000000);
        int check4 = check2 * ((check2 - check3) / 2 + check3) / 1024 * -1337 + check;
        check = check4;
        i++;
    }
    if (check != serial)
        return (1);
    return (0);
}

int     main(void) {
    char            login[32];
    unsigned int    serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    printf("-> Enter Login: ");
    fgets(login, 32, stdin);

    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");
    puts("***********************************");

    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    if (auth(login, serial) == 0) {
        puts("Authenticated!");
        system("/bin/sh");
        return (0);
    }
    return (1);
}