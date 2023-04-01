#!/usr/bin/env bash

# Script finds average UID
getent passwd | cut -d ':' -f3 | ./find_average_from_input.sh 

