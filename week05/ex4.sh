#!/bin/bash

gcc ex4.c -pthread -o ex4

for m in 1 2 4 10 100; do
    echo "m = $m"
    time ./ex4 10000000 $m
done
