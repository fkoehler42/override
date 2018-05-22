#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int         clear_stdin()
{
    
}

int         get_unum()
{
    int number;
    fflush(stdin);
    scanf("%u", (unsigned int)number);
    clear_stdin();
    return number;
}

int         store_number(int number)
{
    printf(" Number: ");
    int nb = get_unum();
    printf(" Index: ");
    int id = get_unum();

}

int         read_number(int number)
{
    printf(" Index: ");
    printf(" Number at data[%u] is %u\n", get_unum(), number); // We don't know where is get_unum()?!
    return (0);
}

int         main(int argc, char **argv)
{
    return (0);
}