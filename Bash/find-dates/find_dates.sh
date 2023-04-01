#!/usr/bin/env bash

regex="(0[1-9]|[12][0-9]|3[01])([\/.])(0[1-9]|1[012])\2(19|20)[0-9][0-9]"

# awk "/${regex}/{print}" text_with_dates.txt
grep -oE "${regex}" text_with_dates.txt
