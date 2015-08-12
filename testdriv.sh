#!/bin/sh
kldload -v ./echo.ko
chmod 666 /dev/echo

#Echo into device
echo -n "test write operation" > /dev/echo

#Now cat to read from the buffer
cat /dev/echo
