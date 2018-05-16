#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void		decrypt(int n) {
	char	s1[] = "Q}|u";			// 0x757c7d51
	char	s2[] = "`sfg";			// 0x67667360
	char	s3[] = "~sfg";			// 0x7b66737e
	char	s4[] = "}|a3";			// 0x33617c7d
	char	c = '\0';

	int s1_len;
	int	whatever;

	s1_len = strlen(s1);
	whatever = 0;
	s1 + s1_len;

	if (strncmp(s1, "Congratulations!", 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
}

void		test(int password, int value) {
	value -= password;
	if ((size_t)value <= 21) {
	//	value = value << 2;
		decrypt(value);
	} else {
		decrypt(rand());
	}
}

int			main(void) {
	int		password;

	srand(time(NULL));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &password);
	test(password, 322424845);
	return (0);
}