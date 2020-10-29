#!/bin/sh

trap "echo sygnal wylapany" 2 3 8 9

while true
do
    echo -n "$$"
    date
    sleep 1
done
