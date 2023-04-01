#!/usr/bin/env bash

sort_array() {

    # set -x
    # local -n arr=$1
    local arr=("$@")

    # arr="$*"

    for ((i=0; i <= $((${#arr[@]} - 2)); ++i))
    do
        for ((j=((i + 1)); j <= ((${#arr[@]} - 1)); ++j))
        do
            if (( ${arr[i]} > ${arr[j]} ))
            then
                tmp=${arr[i]}
                arr[i]=${arr[j]}
                arr[j]=$tmp         
            fi
        done
    done

    echo "RES: ${arr[@]}"
    echo  
}
