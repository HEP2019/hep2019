#!/bin/bash

if test ${#@} -ne 2
then
  echo "use: $0 <width> <height>" >&2
  exit 1
fi

width=$1
height=$2

echo $width $height

for i in `seq 1 $width`
do
  for j in `seq 0 $height`
  do
    if test $((RANDOM % 2)) -eq 0
    then
      echo -n '*'
    else
      echo -n '.'
    fi
  done
  echo
done
