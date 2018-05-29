#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char username[100];

int     verify_user_name(void)
{
    puts("verifying username....\n");
    return strncmp(username, "dat_wil", 7);
}

int     verify_user_pass(char *password)
{
    return strncmp(password, "admin", 5);
}

int     main()
{
    char    password[64] = {0};
    int     verify = 0;

    puts("********* ADMIN LOGIN PROMPT *********");
    printf("Enter Username: ");
    fgets(username, 256, stdin);
    
    verify = verify_user_name();
    if (verify != 0)
    {
        puts("nope, incorrect username...\n");
        return (1);
    }

    puts("Enter Password: ");
    fgets(password, 100, stdin);

    verify = verify_user_pass(password);
    if (verify == 0 || verify != 0)
    {
        puts("nope, incorrect password...\n");
        return (1);
    }
    return (0);
}
