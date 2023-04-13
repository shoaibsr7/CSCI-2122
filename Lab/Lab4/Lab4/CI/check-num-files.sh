#!/bin/bash

result=$(ls Lab4/ | grep -e 'book' -e 'calculator' -v | wc -l)

if (( $result > 0 )); then
    echo "Failure. There is an extra file or folder present in Lab4/."
    exit -1
fi

result=$(ls Lab4/book/ | grep -e 'book.c' -e 'book.h' -v | wc -l)
if (( $result > 0 )); then
    echo "Failure. There is an extra file or folder present in Lab4/book."
    exit -2
fi

result=$(ls Lab4/calculator/ | grep -e 'calculator.c' -e 'calculator.h' -v | wc -l)
if (( $result > 0 )); then
    echo "Failure. There is an extra file or folder present in Lab4/calculator."
    exit -3
fi

exit 0
