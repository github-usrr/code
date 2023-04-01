#!/usr/bin/env bash

echo "Average sales salary:"
awk -F' ' '$3 ~ /sales/ {sum+=$4;ctr++;} END{print sum/ctr;}' employee.txt