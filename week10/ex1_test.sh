#!/bin/bash
gcc ex1.c -o ex1
gcc monitor.c -o monitor

./monitor "~/" &
sleep 1
monitor_pid=$!
echo "monitor pid is:"
echo $monitor_pid
./ex1 "~/" &
sleep 1

mkdir folder1
echo > f1.txt
echo > f2.txt
ls folder1
cat f1.txt
echo "Hello" >> f2.txt
touch f1.txt
rm f1.txt
chmod u=w folder1
rm -r folder1
