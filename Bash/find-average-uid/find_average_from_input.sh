#!/usr/bin/env bash

# Script finds average number from stdin

ctr=0
sum=0

while read n;
do
    ((ctr++))
    sum=$(($sum + $n))
    
done < /dev/stdin

avrg=$(echo "scale=2; ${sum}/${ctr}" | bc)
echo "Average number: ${avrg}"
