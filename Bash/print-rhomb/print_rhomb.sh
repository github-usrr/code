#!/usr/bin/env bash

echo -n "Enter rhomb size (5 to 9): ";
read size

# input validation
if (( size < 5 )) || (( size > 9 )); then
   echo "Error! Incorrect rhomb size"
   exit -1
fi 

# initializing spaces count
spaces=$((size - 1))

# rows loop
for (( i=0; i<$size; i++ ))
do 
   # spaces loop
   for (( j=0; j<$spaces; j++ ))
   do 
       echo -n " "
   done

   # print i+1 dots
   for (( j=0; j<=$i; j++ ))
   do 
       echo -n ". "
   done

   echo # new line
   ((spaces--))
done

# --------repeat printing, but in reverse--------
spaces=0

# rows loop
for (( i=$size; i>0; i-- ))
do 
   # spaces loop
   for (( j=0; j<$spaces; j++ ))
   do 
       echo -n " "
   done

   # print i dots
   for (( j=0; j<$i; j++ ))
   do 
       echo -n ". "
   done

   echo # new line
   ((spaces++))
done


