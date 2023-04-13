#!/bin/bash

m1i1=$(diff m1_output1 output1_1 | wc -c)
m1i2=$(diff m1_output2 output1_2 | wc -c)

m2i1=$(diff m2_output1 output2_1 | wc -c)
m2i2=$(diff m2_output2 output2_2 | wc -c)

if [ $m1i1 -gt 0 ]; then
	printf "Incorrect output on input1 when using calculatorM1.o."
	exit -1
fi

if [ $m1i2 -gt 0 ]; then
	printf "Incorrect output on input2 when using calculatorM1.o."
	exit -2
fi

if [ $m2i1 -gt 0 ]; then
	printf "Incorrect output on input1 when using calculatorM2.o."
	exit -3
fi

if [ $m2i2 -gt 0 ]; then
	printf "Incorrect output on input2 when using calculatorM2.o."
	exit -4
fi
