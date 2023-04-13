#!/bin/bash

result=$(ls -a Lab5/ | grep -e 'array_list' -e 'linked_list' -v | wc -l)

if (( $result > 2 )); then
    echo "Failure. There is an extra file or folder present in Lab5/."
    exit -1
fi

result=$(ls -a Lab5/array_list/ | grep -e 'array_list.c' -e 'array_list.h' -e 'Makefile' -v | wc -l)
if (( $result > 2 )); then
    echo "Failure. There is an extra file or folder present in Lab5/array_list."
    exit -2
fi

result=$(ls -a Lab5/linked_list/ | grep -e 'linked_list.c' -e 'linked_list.h' -e 'Makefile' -v | wc -l)
if (( $result > 2 )); then
    echo "Failure. There is an extra file or folder present in Lab5/linked_list."
    exit -3
fi

exit 0
