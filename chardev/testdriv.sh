#!/bin/sh
kldunload -v ./echo.ko
kldload -v ./echo.ko
chmod 666 /dev/echo

#Echo into device
echo -n "one" > /dev/echo

#Read from device
cat /dev/echo

#Echo into device
echo -n "two" > /dev/echo

#Now cat to read from the buffer
cat /dev/echo
