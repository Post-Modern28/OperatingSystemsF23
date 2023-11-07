#!/bin/bash


input=$(<input.txt)

gcc -o pager pager.c
gcc -o mmu mmu.c
sleep 1
./pager $1 $2 $3 &
echo "Page size is "$1
echo "RAM size is " $2
pager_pid=$!

./mmu $1 "$input" $pager_pid

rm /tmp/ex2/pagetable
