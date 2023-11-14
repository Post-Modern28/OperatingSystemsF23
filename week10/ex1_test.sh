#!/bin/bash
gcc ex1.c -o ex1
gcc monitor.c -o monitor

./monitor "/home/user/For_lab_10" &
sleep 1
monitor_pid=$!
echo "monitor pid is:"
echo $monitor_pid
./ex1 "/home/user/For_lab_10" &
sleep 1

cd /home/user/For_lab_10

echo "Hello world." > myfile1.txt
ln myfile1.txt myfile11.txt
ln myfile1.txt myfile12.txt

./ex1 watched_dir

mv myfile1.txt /tmp/myfile1.txt

echo "Modified content" > myfile11.txt

ln -s /tmp/myfile1.txt myfile13.txt

echo "New content" > /tmp/myfile1.txt

./ex1 watched_dir

