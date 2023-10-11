#!/bin/bash

gcc ex3.c -pthread -o ex3

for m in 1 2 4 10 100; do
    echo "m = $m"
    time ./ex3 10000000 $m
done
