#include <stdio.h>

int     main()
{
	memset();
    puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	char *username = fgets(buf, 256, stdin);
	if (verify_user_name(username))
	{
		puts("Enter Password: ");
		char *userpass = fgets(buf, 100, stdin);
		if (verify_user_pass(userpass))
		{

		}
		else
			puts("nope, incorrect password...\n");
	}
    return (0);
}
