#!/bin/bash

gcc @../opcje ../ori.c -o ori.e -lm

for f in $(ls *.in | sort -n); do

    echo $f
    
    ./ori.e < $f > ori.out
    
    echo ${f%.in}.out
    
    if diff -wq ori.out ${f%.in}.out; then
        echo Accepted!
    else
        break
    fi
    
done
