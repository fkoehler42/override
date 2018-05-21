import struct

def keygen(login):
    assert(len(login) > 5 and len(login) <= 32)
    cst = (ord(login[3]) ^ 0x1337) + 0x5eeded
    # print "cst = ", cst
    for letter in login:
        if ord(letter) <= 31:
            break
        val1 = ord(letter) ^ cst
        print "val1 = ", val1
        val2 = (0x88233b2b * val1) / 0x100000000
        print "val2 = ", val2
        val3 = val1 + (-1337) * ((val1 - val2) / 2 + val2) / 1024 + cst
        print "val3 = ", val3
        cst = val3
        # print "new cst = ", cst
    print val3

keygen("AAAAAA")
# 6229050
# struct.unpack('>i', bytes('9DA92DAB', 'utf-8').decode('hex'))