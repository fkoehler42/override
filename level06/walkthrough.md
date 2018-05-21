# level06

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```console
level06@OverRide:~$ checksec --file ./level06
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   ./level06
```

First of all, we see that the binary is protected against code execution on stack, so it does not matter if we find a way to inject some code or to redirect the execution flow to any instructions stored on the stack.

From our analysis of the disassembled code, here is what the program does :

- The `main` function calls `fgets` to get an input string of 32 bytes max (login) and `scanf` to get an unsigned integer (serial). Then, it sends these values to a function `auth`, and expect its return value to be `0` in order to spawn a shell thanks to `system`.

- The `auth` function first replaces the trailing `\n` of login string with a `\0` and store its length on the stack. If that length is above 6 characters, the function returns `1` and the program quits immediately.

- An anti-debugging protection is present; actually it is a call to `ptrace` which returns `-1` when executed in a debugger, so we will jump the set of associated instructions to follow the execution flow inside GDB.

- Then come the serialization steps : an initial 'check' value is set, depending on the third character of login and two constants. This value is used in a `while` loop, iterating on the login string, that performs some operations to generate a new check value. We also notice that we must use only printable characters to fill the login, since a test is done for each one. At the end of the loop, the final value is compared to 'serial' and if they are equal the function returns `0` so the `main` calls `system` function.

## Exploit

Our first approach is to run the executable in GDB, to send a simple string of six 'A' to `fgets` and go through the differents steps until we reach the final comparison. This way we will be able to get the serial value expected.

We set two breakpoints; the first one to jump over the checking of the return value from `ptrace` call , and the second one to get the final value expected.

```gdb
gdb-peda$ pdisas auth
Dump of assembler code for function auth:
   0x08048748 <+0>:      push   ebp
   0x08048749 <+1>:      mov    ebp,esp
   0x0804874b <+3>:      sub    esp,0x28
   [...]
   0x08048796 <+78>:     mov    DWORD PTR [esp+0xc],0x0
   0x0804879e <+86>:     mov    DWORD PTR [esp+0x8],0x1
   0x080487a6 <+94>:     mov    DWORD PTR [esp+0x4],0x0
   0x080487ae <+102>:    mov    DWORD PTR [esp],0x0
   0x080487b5 <+109>:    call   0x80485f0 <ptrace@plt>          ; ptrace(0, 0, 1, NULL)
   0x080487ba <+114>:    cmp    eax,0xffffffff                  ; ptrace return value compared to -1
   0x080487bd <+117>:    jne    0x80487ed <auth+165>            ; first breakpoint
   0x080487bf <+119>:    mov    DWORD PTR [esp],0x8048a68
   0x080487c6 <+126>:    call   0x8048590 <puts@plt>
   0x080487cb <+131>:    mov    DWORD PTR [esp],0x8048a8c
   0x080487d2 <+138>:    call   0x8048590 <puts@plt>
   0x080487d7 <+143>:    mov    DWORD PTR [esp],0x8048ab0
   0x080487de <+150>:    call   0x8048590 <puts@plt>
   0x080487e3 <+155>:    mov    eax,0x1
   0x080487e8 <+160>:    jmp    0x8048877 <auth+303>
   0x080487ed <+165>:    mov    eax,DWORD PTR [ebp+0x8]         ; we jump here as if ptrace has returned a positive value
   [...]
   0x08048863 <+283>:    mov    eax,DWORD PTR [ebp+0xc]
   0x08048866 <+286>:    cmp    eax,DWORD PTR [ebp-0x10]        ; second breakpoint
   0x08048869 <+289>:    je     0x8048872 <auth+298>
   0x0804886b <+291>:    mov    eax,0x1
   0x08048870 <+296>:    jmp    0x8048877 <auth+303>
   0x08048872 <+298>:    mov    eax,0x0
   0x08048877 <+303>:    leave
   0x08048878 <+304>:    ret
End of assembler dump.
```

Here are the commands used in GDB (the output has been truncated to make it as clear as possible) :

```gdb
gdb-peda$ b *0x080487bd
Breakpoint 1 at 0x80487bd
gdb-peda$ b *0x08048866
Breakpoint 2 at 0x8048866
gdb-peda$ run
***********************************
*		level06		  *
***********************************
-> Enter Login: AAAAAA
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 123

   0x80487ba <auth+114>:	cmp    eax,0xffffffff
=> 0x80487bd <auth+117>:	jne    0x80487ed <auth+165>
   0x80487bf <auth+119>:	mov    DWORD PTR [esp],0x8048a68
   0x80487c6 <auth+126>:	call   0x8048590 <puts@plt>
                                                              JUMP is NOT taken

Breakpoint 1, 0x080487bd in auth ()
gdb-peda$ jump *0x080487ed

   0x8048863 <auth+283>:	mov    eax,DWORD PTR [ebp+0xc]
=> 0x8048866 <auth+286>:	cmp    eax,DWORD PTR [ebp-0x10]
   0x8048869 <auth+289>:	je     0x8048872 <auth+298>
   0x804886b <auth+291>:	mov    eax,0x1

Breakpoint 2, 0x08048866 in auth ()
gdb-peda$ x $ebp-0x10
0xffffd698:	0x005f0c3a
```

Here we are ! the value expected for the login string "AAAAAA" is `0x005f0c3a` or `6229050` in decimal. Let's run the executable again (out of GDB) and provide it the right value.

```console
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: AAAAAA
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6229050
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```