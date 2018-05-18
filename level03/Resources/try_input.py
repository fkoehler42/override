import os

cases = [1,2,3,4,5,6,7,8,9,16,17,18,19,20,21]
constant = 0x1337d00d
print "--- Start"
for l in cases:
    arg = constant - l
    cmd = "(echo \"" + str(arg) + "\"; cat) | ./level03"
    print "Testing\t\t" + cmd
    os.system(cmd)
print "--- Done"
