#!/bin/bash

gcc -o pager pager.c
gcc -o mmu mmu.c
sleep 1
./pager $1 $3 &

pager_pid=$!

./mmu $1 "$2" $pager_pid

rm /tmp/ex2/pagetable
