#!/bin/bash

ARGS=$1
TIMEOUT=$2
COUNT=1

echo "Test Application"
echo "args: $ARGS"
while true;
do
   echo $1 $COUNT
   let COUNT=$COUNT+1 
   sleep $2;
done

exit 1
