#!/bin/sh
################################################################################
# This script install automatically all required                               #
# package and configuration for OverRide                                       #
################################################################################


# Password

echo "level00:level00" | chpasswd
echo "level01:uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL" | chpasswd
echo "level02:PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv" | chpasswd
echo "level03:Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H" | chpasswd
echo "level04:kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf" | chpasswd 
echo "level05:3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN" | chpasswd
echo "level06:h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq" | chpasswd
echo "level07:GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8" | chpasswd
echo "level08:7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC" | chpasswd
echo "level09:fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S" | chpasswd
echo "end:j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE" | chpasswd

# create .pass

echo "uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL" > /home/users/level01/.pass
echo "PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv" > /home/users/level02/.pass
echo "Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H" > /home/users/level03/.pass
echo "kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf" > /home/users/level04/.pass
echo "3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN" > /home/users/level05/.pass
echo "h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq" > /home/users/level06/.pass
echo "GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8" > /home/users/level07/.pass
echo "7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC" > /home/users/level08/.pass
echo "fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S" > /home/users/level09/.pass
echo "j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE" > /home/users/end/.pass

# RAZ ACL
setfacl -R -b /home/users/;
chmod 511 /home/users;
chmod 500 /home/users/*;

# LVL0
setfacl -m d:u:level00:r-x /home/users/level00;
setfacl -m u:level00:r-x /home/users/level00;
chown level01:users /home/users/level00/level00;
chmod  6700 /home/users/level00/level00;
setfacl -m u:level00:r-x /home/users/level00/level00;
setfacl -m u:level00:r-x /home/users/level00/level00;

# LVL1
setfacl -m d:u:level01:r-x /home/users/level01;
setfacl -m u:level01:r-x /home/users/level01;
chown level02:users /home/users/level01/level01;
chmod  6700 /home/users/level01/level01;
setfacl -m u:level02:r-x /home/users/level01/level01;
setfacl -m u:level01:r-x /home/users/level01/level01;
chown level01:level01 /home/users/level01/.pass;
setfacl -m u:level01:r-- /home/users/level01/.pass;

# LVL2
setfacl -m d:u:level02:r-x /home/users/level02;
setfacl -m u:level02:r-x /home/users/level02;
chown level03:users /home/users/level02/level02;
chmod  6700 /home/users/level02/level02;
setfacl -m u:level03:r-x /home/users/level02/level02;
setfacl -m u:level02:r-x /home/users/level02/level02;
chown level02:level02 /home/users/level02/.pass;
setfacl -m u:level02:r-- /home/users/level02/.pass;

# LVL3
setfacl -m d:u:level03:r-x /home/users/level03;
setfacl -m u:level03:r-x /home/users/level03;
chown level04:users /home/users/level03/level03;
chmod  6700 /home/users/level03/level03;
setfacl -m u:level04:r-x /home/users/level03/level03;
setfacl -m u:level03:r-x /home/users/level03/level03;
chown level03:level03 /home/users/level03/.pass;
setfacl -m u:level03:r-- /home/users/level03/.pass;

# LVL4
setfacl -m d:u:level04:r-x /home/users/level04;
setfacl -m u:level04:r-x /home/users/level04;
chown level05:users /home/users/level04/level04;#
chmod  6700 /home/users/level04/level04;
setfacl -m u:level05:r-x /home/users/level04/level04;#
setfacl -m u:level04:r-x /home/users/level04/level04;
chown level04:level04 /home/users/level04/.pass;
setfacl -m u:level04:r-- /home/users/level04/.pass;

# LVL5
setfacl -m d:u:level05:r-x /home/users/level05;
setfacl -m u:level05:r-x /home/users/level05;
chown level06:users /home/users/level05/level05;#
chmod  6700 /home/users/level05/level05;
setfacl -m u:level06:r-x /home/users/level05/level05;#
setfacl -m u:level05:r-x /home/users/level05/level05;
chown level05:level05 /home/users/level05/.pass;
setfacl -m u:level05:r-- /home/users/level05/.pass;

# LVL6
setfacl -m d:u:level06:r-x /home/users/level06;
setfacl -m u:level06:r-x /home/users/level06;
chown level07:users /home/users/level06/level06;#
chmod  6700 /home/users/level06/level06;
setfacl -m u:level07:r-x /home/users/level06/level06;#
setfacl -m u:level06:r-x /home/users/level06/level06;
chown level06:level06 /home/users/level06/.pass;
setfacl -m u:level06:r-- /home/users/level06/.pass;

# LVL7
setfacl -m d:u:level07:r-x /home/users/level07;
setfacl -m u:level07:r-x /home/users/level07;
chown level08:users /home/users/level07/level07;#
chmod  6700 /home/users/level07/level07;
setfacl -m u:level08:r-x /home/users/level07/level07;#
setfacl -m u:level07:r-x /home/users/level07/level07;
chown level07:level07 /home/users/level07/.pass;
setfacl -m u:level07:r-- /home/users/level07/.pass;

# LVL8
setfacl -m d:u:level08:r-x /home/users/level08;
setfacl -m u:level08:r-x /home/users/level08;
setfacl -m d:u:level09:r-x /home/users/level08;
setfacl -m u:level09:r-x /home/users/level08;
chown level09:users /home/users/level08/level08;#
chmod  6700 /home/users/level08/level08;
chmod -R 770 /home/users/level08/backups;
setfacl -Rb /home/users/level08/backups;
setfacl -m u:level09:r-x /home/users/level08/level08;
#setfacl -R -m d:u:level09:rwx /home/users/level08/backups;
#setfacl -R -m u:level09:rwx /home/users/level08/backups;
setfacl -m u:level08:r-x /home/users/level08/level08;
#setfacl -R -m d:u:level08:rwx /home/users/level08/backups;
#setfacl -R -m u:level08:rwx /home/users/level08/backups;
#setfacl -m u:level08:rwx /home/users/level08/backups/.log;
chown level08:level08 /home/users/level08/.pass;
setfacl -m u:level08:r-- /home/users/level08/.pass;

# LVL9
setfacl -m d:u:level09:r-x /home/users/level09;
setfacl -m u:level09:r-x /home/users/level09;
chown end:users /home/users/level09/level09;#
chmod  6700 /home/users/level09/level09;
setfacl -m u:end:r-x /home/users/level09/level09;#
setfacl -m u:level09:r-x /home/users/level09/level09;
chown level09:level09 /home/users/level09/.pass;
setfacl -m u:level09:r-- /home/users/level09/.pass;


# END
setfacl -m d:u:end:r-x /home/users/end;
setfacl -m u:end:r-x /home/users/end;
chown end:users /home/users/end/end;#
chmod  6700 /home/users/end/end;
setfacl -m u:end:r-x /home/users/end/end;#
setfacl -m u:end:r-x /home/users/end/end;
chown end:end /home/users/end/.pass;
setfacl -m u:end:r-- /home/users/end/.pass;

