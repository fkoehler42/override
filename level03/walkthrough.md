# level03

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

```console
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   ./level03
```

## Exploit

```python
>>> l = [1,2,3,4,5,6,7,8,9,16,17,18,19,20,21]
>>> a2 = 0x1337d00d
>>> a2
322424845
>>> for a1 in l:
...     print a2 - a1
...
322424844
322424843
322424842
322424841
322424840
322424839
322424838
322424837
322424836
322424829
322424828
322424827
322424826
322424825
322424824
```

```console
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
