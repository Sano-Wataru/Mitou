#!/bin/bash

str=$1

if [ -n "$str" ]; then
  if [ $str = 's' ]; then
      ./exec/server
  elif [ $str = 'c' ]; then
      ./exec/client
  else
    echo "$str is not valid option. Please input 's' or 'c'."
  fi
else
  echo "Please input 's' or 'c' as an argument."
fi