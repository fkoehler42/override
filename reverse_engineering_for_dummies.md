# Reverse engineering for dummies

You have a binary, you wan't to reverse it?

## Commands:

Okay, so here are some usefull commands and tool to test on your `executable`:

```console
$> file executable
```

```console
$> hexdump -C executable
```

```console
$> strings executable
```

```console
$> objdump -d executable
```

```console
$> objdump -x executable | less         # headers
```

```console
$> strace executable                    # trace system calls and signals
```

```console
$> ltrace executable                    # trace library functions
```

## Softwares and websites:

- Softwares:
    - [Hopper](https://www.hopperapp.com/)
    - [radare 2](https://github.com/radare/radare2) - The best!
    - [pwntools](https://github.com/Gallopsled/pwntools) - CTF framework and exploit development library.
- Websites:
    - [Online desassembler](https://onlinedisassembler.com/odaweb/) - Like radare2 but online.
    - [Online decompiler](https://retdec.com/decompilation/) - Useful for less than 10 Mb files.

## radare2

```console
$> r2 executable
```

First run:

```
[0x004004d0]> aaa
```

to analyze functions. Use:

```
[0x004004d0]> afl
```

to print available functions. To get help do:

```
[0x004004d0]> ?
```

Go to a function with:

```
[0x004004d0]> s sym.main
```

for example. Then use:

```
[0x004004d0]> pdf
```

to display disassembler code. You can enter visual mode with:

```
[0x004004d0]> VV
```

In `VV` mode:

- Use `TAB` and `Shift + TAB` to switch between blocks.
- When you have a block selected, move it thanks to `Shift + [hjkl]`.
- `p` is used to cycle between different representations.


You can use Radare2 to debug a program. To do so, use:

```
$> r2 -d executable
```

