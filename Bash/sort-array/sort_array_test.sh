#!/usr/bin/env bash

source sort_array.sh

declare -a ar=(5 3 4 1 2 9 10 8 7 6)
echo ${ar[@]}
sort_array "${ar[@]}"
echo ${ar[@]}

