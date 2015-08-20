#!/bin/sh
#delete object and remake

rm echo.ko
make

kldunload -v ./echo.ko
kldload -v ./echo.ko
chmod 666 /dev/echo

#Generate random number of characters
STR=$(cat /dev/random | tr -dc 'a-zA-Z0-9' | fold -w 257 | head -n 1)
#echo $STR

#Echo into device
#echo -n $STR > /dev/echo

#Now cat to read from the buffer
cat /dev/echo

cc -o mapdriv.o mapdriv.c
./mapdriv.o

cat /dev/echo
