#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int         main(void) {
    unsigned int    i = 0;          // esp+0x8c
    char            buf[100];       // esp+0x28

    fgets(buf, 100, stdin);
    i = 0;
    while (strlen(buf) >= i) {
        if (buf[i] > '@' && buf[i] <= 'Z')
            buf[i] += 32;
        i++;
    }
    printf(buf);
    exit(0);
}