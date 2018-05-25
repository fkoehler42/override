# Override

## Resources

- 🇬🇧 [Github book about hacking](https://trailofbits.github.io/ctf/)
- 🇬🇧 [Some useful online tools](https://defuse.ca/) - [This](https://defuse.ca/online-x86-assembler.htm) can help you
  create shellcode.
- 🇬🇧 [Buffer Overflow EIP Offset String
  Generator](http://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/)
- 🇬🇧 [Smash stack](http://insecure.org/stf/smashstack.html)
- 🇫🇷 [Introduction aux buffer overflows](https://zestedesavoir.com/articles/100/introduction-aux-buffer-overflows/)
- 🇫🇷 [Introduction à la rétroingénierie de
  binaires](https://zestedesavoir.com/articles/97/introduction-a-la-retroingenierie-de-binaires/)
- 🇫🇷 [Écrivez votre premier shellcode en asm x86
  !](https://zestedesavoir.com/articles/158/ecrivez-votre-premier-shellcode-en-asm-x86/)

### Shell-codes

- [Shellcodes database](http://shell-storm.org/shellcode/)

## Tips

### Commands

- `checksec --file your_binary` displays informations about the executable protections (relro, stack canary...).
- `readelf -l your_elf_binary | grep GNU_STACK` displays the stack flags, useful to quickly know if you can execute some
  code from it.

### Shellcodes

If debugging shellcode, we can use `\xcc` (int3) to stop program and return to debugger. It's a breakpoint instruction
(used by GDB).

### Python tips

You can use `struct` to convert the integer number to a binary string easily.
[Link](https://docs.python.org/2/library/struct.html).

```python
>>> import struct
>>> struct.pack("I", 0x080483f4)
'\xf4\x83\x04\x08'
```

Generate easily a string like `AAAABBBBCCCC...` (the full length is `104`):

```python
>>> "".join(x for x in string.ascii_uppercase for _ in range(4))
'AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ'
```

### Setup peda

You can use [GDB peda](https://github.com/longld/peda) to enhance your GDB.

```bash
#!/bin/bash -e
FILE="utils.py skeleton.py six.py shellcode.py nasm.py config.py"

mkdir -p /tmp/peda/lib

cd /tmp/peda
curl -k -O https://raw.githubusercontent.com/longld/peda/master/peda.py
cd lib

for i in $FILE
    do curl -k -O https://raw.githubusercontent.com/longld/peda/master/lib/$i
done

cd /tmp/peda
chmod -R +rx .
cd $HOME

echo "\033[31mNE PAS OUBLIER l'ALIAS GDB :\033[0m"
echo 'alias gdb="/usr/bin/gdb -x /tmp/peda/peda.py -q "'
```
