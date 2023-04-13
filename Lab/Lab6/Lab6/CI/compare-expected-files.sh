#!/bin/bash

in=$(diff in_expected in_out | wc -c)
pr=$(diff pre_expected pre_out | wc -c)
po=$(diff post_expected post_out | wc -c)
rv=$(diff rev_expected rev_out | wc -c)

if [ $in -gt 0 ]; then
	printf "in_out does not match the expected file. Your file is not printing in-order correctly for 10,000 values."
	exit -1
fi

if [ $pr -gt 0 ]; then
	printf "pre_out does not match the expected file. Your file is not printing pre-order correctly for 10,000 values."
	exit -2
fi

if [ $po -gt 0 ]; then
	printf "post_out does not match the expected file. Your file is not printing post-order correctly for 10,000 values."
	exit -3
fi

if [ $rv -gt 0 ]; then
	printf "rev_out does not match the expected file. Your file is not printing reverse-order correctly for 10,000 values."
	exit -4
fi
