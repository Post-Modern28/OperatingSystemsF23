#!/bin/bash
./ex1 &

sleep 1 

pid=$(pgrep ex1)
echo "PID: $pid"
addr=$(cat /proc/$pid/maps | grep /dev/zero | awk '{print $1}')

start=$(echo $addr | cut -d'-' -f1)
end=$(echo $addr | cut -d'-' -f2)

start="0x$start"
end="0x$end"


pass=$(sudo xxd -s $start -l $(("$end-$start")) /proc/$pid/mem | grep pass)
if [ -z "$pass" ]; then
    echo "Password not found"
    sudo pkill ex1
    exit 1
fi

pass=$(echo $pass | cut -d':' -f3 | cut -c1-8)
echo "Password: $pass"

sudo pkill ex1
