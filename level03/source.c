#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void		decrypt(int mask) {
	int				str = 0x757c7d51;	// "Q}|u"
	int				str2 = 0x67667360;	// "`sfg"
	int				str3 = 0x7b66737e;	// "~sfg"
	int				str4 = 0x33617c7d;	// "}|a3"
	char			c = 0;
	unsigned int	str_len = strlen((char*)&str);
	int				i = 0;
	char			*tmp;

	while (i < str_len) {
		tmp = (char*)&str + i;
		*tmp = (int)*tmp ^ mask;
		i++;
	}
	if (strncmp((char*)&str, "Congratulations!", 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
}

void		test(int password, int value) {
	int		test_value;

	switch (value - password) {
		case 1: {
			decrypt(1);
			break;
		}
		case 2: {
			decrypt(2);
			break;
		}
		case 3: {
			decrypt(3);
			break;
		}
		case 4: {
			decrypt(4);
			break;
		}
		case 5: {
			decrypt(5);
			break;
		}
		case 6: {
			decrypt(6);
			break;
		}
		case 7: {
			decrypt(7);
			break;
		}
		case 8: {
			decrypt(8);
			break;
		}
		case 9: {
			decrypt(9);
			break;
		}
		case 16: {
			decrypt(16);
			break;
		}
		case 17: {
			decrypt(17);
			break;
		}
		case 18: {
			decrypt(18);
			break;
		}
		case 19: {
			decrypt(19);
			break;
		}
		case 20: {
			decrypt(20);
			break;
		}
		case 21: {
			decrypt(21);
			break;
		}
		default :
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
	test(password, 0x1337d00d);	// 322424845
	
	return (0);
}