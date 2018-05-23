//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) 2018 Retargetable Decompiler <info@retdec.com>
//

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------ Structures ------------------------

struct _IO_FILE {
    int32_t e0;
};

// ------------------- Function Prototypes --------------------

int32_t clear_stdin(void);
int32_t get_unum(void);
int32_t read_number(int32_t a1);
int32_t store_number(int32_t a1);

// ------------------------ Functions -------------------------

// Address range: 0x80485c4 - 0x80485e6
int32_t clear_stdin(void) {
    struct _IO_FILE * v1 = NULL; // 0x804a040
    struct _IO_FILE * v2 = NULL; // 0x804a060
    bool v3 = false;
    // 0x80485c4
    // branch -> 0x80485d1
    int32_t c; // 0x80485d1
    while (true) {
        // 0x80485d1
        c = getchar();
        char v4 = c;
        if (v4 == 10) {
            // 0x80485e5
            return c;
        }
        // 0x80485df
        if (v4 == -1) {
            // break -> 0x80485e5
            break;
        }
        // continue -> 0x80485d1
    }
    // 0x80485e5
    return c;
}

// Address range: 0x80485e7 - 0x804861e
int32_t get_unum(void) {
    struct _IO_FILE * v1; // 0x804a040
    bool v2;
    int32_t result = 0; // bp-16
    struct _IO_FILE * stream; // 0x804a060
    fflush(stream);
    scanf("%u", &result);
    clear_stdin();
    return result;
}

// Address range: 0x8048630 - 0x80486d6
int32_t store_number(int32_t a1) {
    struct _IO_FILE * v1; // 0x804a040
    struct _IO_FILE * v2; // 0x804a060
    bool v3;
    // 0x8048630
    printf(" Number: ");
    int32_t v4 = get_unum(); // 0x8048651
    printf(" Index: ");
    int32_t v5 = get_unum(); // 0x8048666
    uint64_t v6 = 0xaaaaaaab * (int64_t)v5 / 0x200000000; // 0x804867a10
    if (v5 == (int32_t)(2 * v6) + (int32_t)v6) {
        // 0x8048697
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        // branch -> 0x80486d5
        // 0x80486d5
        return 1;
    }
    // 0x804868a
    if ((v4 & -0x1000000) != -0x49000000) {
        // 0x80486c2
        // branch -> 0x80486d5
        // 0x80486d5
        return 0;
    }
    // 0x8048697
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    // branch -> 0x80486d5
    // 0x80486d5
    return 1;
}

// Address range: 0x80486d7 - 0x8048722
int32_t read_number(int32_t a1) {
    struct _IO_FILE * v1; // 0x804a040
    struct _IO_FILE * v2; // 0x804a060
    bool v3;
    // 0x80486d7
    printf(" Index: ");
    int32_t v4; // 0x8048702
    printf(" Number at data[%u] is %u\n", get_unum(), v4);
    return 0;
}

// Address range: 0x8048723 - 0x80489ff
int main(int argc, char ** argv) {
    struct _IO_FILE * v1; // 0x804a060
    int32_t str3 = 0; // bp-40
    int32_t v2;
    int32_t v3 = &v2; // 0x8048791_0
    memset((char *)&v2, 0, 100);
    int32_t v4; // 0x8048834
    int32_t * v5; // 0x804883d_0
    int32_t * v6; // bp+024
    int32_t * str2; // bp+028
    int32_t v7; // 0x8048878_0
    struct _IO_FILE * stream; // 0x804a040
    int32_t v8;
    int32_t len2;
    int32_t len3;
    uint32_t strncmp_rc;
    bool v9; // 0x80488d0
    bool v10;
    if (*(int32_t *)argv != 0) {
        int32_t * str = (int32_t *)argv;
        int32_t len = strlen((char *)*str);
        memset((char *)*str, 0, len);
        int32_t v11 = (int32_t)argv + 4; // 0x80487e5
        while (*(int32_t *)v11 != 0) {
            // 0x80487a7
            str = (int32_t *)v11;
            len = strlen((char *)*str);
            memset((char *)*str, 0, len);
            v11 += 4;
            // continue -> 0x80487a7
        }
        // 0x8048839
        v6 = (int32_t *)v8;
        if (*v6 != 0) {
            str2 = v6;
            len2 = strlen((char *)*str2);
            memset((char *)*str2, 0, len2);
            v4 = v8 + 4;
            v5 = (int32_t *)v4;
            while (*v5 != 0) {
                // 0x80487f6
                str2 = v5;
                len2 = strlen((char *)*str2);
                memset((char *)*str2, 0, len2);
                v4 += 4;
                v5 = (int32_t *)v4;
                // continue -> 0x80487f6
            }
            // 0x8048843
            puts("----------------------------------------------------\n
                  Welcome to wil's crappy number storage service!   \n
                  ----------------------------------------------------\n 
                  Commands:                                          \n
                  store - store a number into the data storage    \n
                  read  - read a number from the data storage     \n
                  quit  - exit the program                        \n
                  ----------------------------------------------------\n
                  wil has reserved some storage :>                 \n
                  ----------------------------------------------------\n");
            v7 = &str3;
            // branch -> 0x804884f
            while (true) {
                // 0x804884f
                printf("Input command: ");
                fgets((char *)&str3, 20, stream);
                len3 = strlen((char *)&str3);
                strncmp_rc = strncmp((char *)&str3, "store", 5);
                v10 = strncmp_rc % 2 == 0;
                v9 = len3 == 0;
                if ((0x1000000 * ((((int32_t)(v9 || strncmp_rc % 2 == 0) || v7 & -256) ^ 1) - (int32_t)v9) || 0xffffff) < 0x1ffffff) {
                  lab_0x8048965_3:
                    // 0x8048965
                    if (store_number(v3) != 0) {
                      lab_0x804896f:
                        // 0x804896f
                        printf(" Failed to do %s command\n", &str3);
                        // branch -> 0x80489a1
                      lab_0x80489a1:
                        // 0x80489a1
                        str3 = 0;
                        // branch -> 0x804884f
                        continue;
                    }
                } else {
                  lab_0x80488f8_3:;
                    uint32_t strncmp_rc2 = strncmp((char *)&str3, "read", 4);
                    v10 = strncmp_rc2 % 2 == 0;
                    bool v12 = false; // 0x8048911
                    if ((0x1000000 * ((((int32_t)(v12 || strncmp_rc2 % 2 == 0) || v7 & -256) ^ 1) - (int32_t)v12) || 0xffffff) < 0x1ffffff) {
                        // 0x8048965
                        read_number(v3);
                        // branch -> 0x8048989
                        // 0x8048989
                        printf(" Completed %s command successfully\n", &str3);
                        // branch -> 0x80489a1
                        goto lab_0x80489a1;
                    } else {
                        uint32_t strncmp_rc3 = strncmp((char *)&str3, "quit", 4);
                        v10 = strncmp_rc3 % 2 == 0;
                        bool v13 = false; // 0x8048952
                        if ((0x1000000 * ((((int32_t)(v13 || strncmp_rc3 % 2 == 0) || v7 & -256) ^ 1) - (int32_t)v13) || 0xffffff) < 0x1ffffff) {
                            // 0x80489cf
                            int32_t v14; // 0x8048741
                            int32_t v15; // 0x80489dd
                            if (v15 != v14) {
                                // 0x80489e5
                                __stack_chk_fail();
                                // branch -> 0x80489ea
                            }
                            // 0x80489ea
                            return 0;
                        }
                        // 0x8048965
                        // branch -> 0x804896f
                        goto lab_0x804896f;
                    }
                  lab_0x80489a1_2:
                    // 0x80489a1
                    str3 = 0;
                    // branch -> 0x804884f
                    continue;
                }
                // 0x8048989
                printf(" Completed %s command successfully\n", &str3);
                // branch -> 0x80489a1
                goto lab_0x80489a1_2;
            }
        }
        // 0x8048843
        puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n");
        v7 = &str3;
        // branch -> 0x804884f
        while (true) {
            // 0x804884f
            printf("Input command: ");
            fgets((char *)&str3, 20, stream);
            len3 = strlen((char *)&str3);
            strncmp_rc = strncmp((char *)&str3, "store", 5);
            v10 = strncmp_rc % 2 == 0;
            v9 = len3 == 0;
            if ((0x1000000 * ((((int32_t)(v9 || strncmp_rc % 2 == 0) || v7 & -256) ^ 1) - (int32_t)v9) || 0xffffff) < 0x1ffffff) {
                goto lab_0x8048965_3;
            }
            goto lab_0x80488f8_3;
        }
    }
    // 0x8048839
    v6 = (int32_t *)v8;
    if (*v6 != 0) {
        str2 = v6;
        len2 = strlen((char *)*str2);
        memset((char *)*str2, 0, len2);
        v4 = v8 + 4;
        v5 = (int32_t *)v4;
        while (*v5 != 0) {
            // 0x80487f6
            str2 = v5;
            len2 = strlen((char *)*str2);
            memset((char *)*str2, 0, len2);
            v4 += 4;
            v5 = (int32_t *)v4;
            // continue -> 0x80487f6
        }
        // 0x8048843
        puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n");
        v7 = &str3;
        // branch -> 0x804884f
        while (true) {
            // 0x804884f
            printf("Input command: ");
            fgets((char *)&str3, 20, stream);
            len3 = strlen((char *)&str3);
            strncmp_rc = strncmp((char *)&str3, "store", 5);
            v10 = strncmp_rc % 2 == 0;
            v9 = len3 == 0;
            if ((0x1000000 * ((((int32_t)(v9 || strncmp_rc % 2 == 0) || v7 & -256) ^ 1) - (int32_t)v9) || 0xffffff) < 0x1ffffff) {
                goto lab_0x8048965_3;
            }
            goto lab_0x80488f8_3;
        }
    }
    // 0x8048843
    puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n");
    v7 = &str3;
    // branch -> 0x804884f
    while (true) {
        // 0x804884f
        printf("Input command: ");
        fgets((char *)&str3, 20, stream);
        len3 = strlen((char *)&str3);
        strncmp_rc = strncmp((char *)&str3, "store", 5);
        v10 = strncmp_rc % 2 == 0;
        v9 = len3 == 0;
        if ((0x1000000 * ((((int32_t)(v9 || strncmp_rc % 2 == 0) || v7 & -256) ^ 1) - (int32_t)v9) || 0xffffff) < 0x1ffffff) {
            goto lab_0x8048965_3;
        }
        goto lab_0x80488f8_3;
    }
}

// --------------- Dynamically Linked Functions ---------------

// void __stack_chk_fail(void);
// int fflush(FILE * stream);
// char * fgets(char * restrict s, int n, FILE * restrict stream);
// int getchar(void);
// void * memset(void * s, int c, size_t n);
// int printf(const char * restrict format, ...);
// int puts(const char * s);
// int scanf(const char * restrict format, ...);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (4.6.3)
// Detected functions: 5
// Decompiler release: v2.2.1 (2016-09-07)
// Decompilation date: 2018-05-22 10:17:15