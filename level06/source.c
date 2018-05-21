#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int     auth(char *login, unsigned int serial) {
    unsigned int    check;
    int             i;


    *(login + strcspn(login, "\n")) = '\0';
    serial = strnlen(login, 32);
    if (serial <= 5)
        return (1);
    if (ptrace(0, 0, 1, NULL) == -1) {
        puts("\033[32m.---------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !!  |");
        puts("\033[32m'---------------------------'");
        return (1);
    }
    check = (unsigned int)login[3] ^ 4919 + 6221293;
    i = 0;
    while (i < serial) {
        if (login[i] <= 31)
            return (1);
    //    2284010283 * login[i] ^ check
        i++;
    }
    return (0);
}

int     main(void) {
    char            login[32];                      // 0x2c
    unsigned int    serial;                         // 0x28

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