"""
Little serial keygen. Example: keygen("AAAAAA") should give you 6229050.
"""
import argparse
import struct

def keygen(login):
    assert(len(login) > 5 and len(login) <= 32)
    cst = (ord(login[3]) ^ 0x1337) + 0x5eeded
    for letter in login:
        if ord(letter) <= 31:
            break
        val1 = ord(letter) ^ cst
        val2 = 0x88233b2b * val1 / 0x100000000
        val3 = val1 + ((val1 - val2) / 2 + val2) / 1024 * -1337 + cst
        cst = val3
    print "The serial corresponding to " + str(login) + " is: " + str(val3)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Little serial keygen.')
    parser.add_argument('login', type=str, help='login must be between 5 and 32 characters')
    args = vars(parser.parse_args())
    keygen(args["login"])
