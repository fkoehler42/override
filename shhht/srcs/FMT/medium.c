/*
	gcc -m32 -z execstack -z norelro -fno-stack-protector -o FMT_medium medium.c
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 int main(int argc, char *argv[])
 {
     int i = 0;
     char buf[100];
 
     fgets(buf, 100, stdin);
 
     for (i = 0; i < strlen(buf); i++)
         if (buf[i] >= 'A' && buf[i] <= 'Z')
             buf[i] = buf[i] ^ 0x20;
 
     printf(buf);
     exit(EXIT_SUCCESS);
     return EXIT_FAILURE;
 }
