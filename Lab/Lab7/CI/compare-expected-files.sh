#!/bin/bash

dfsWC=$(cat dfs_out | wc -c)
bfsWC=$(cat bfs_out | wc -c)
dfsDF=$(diff dfs_expected dfs_out | wc -c)
bfsDF=$(diff bfs_expected bfs_out | wc -c)

if [ $dfsWC -eq 0 ]; then
	printf "Your dfs program does not produce output."
	exit 100
fi

if [ $bfsWC -eq 0 ]; then
	printf "Your bfs program does not produce output."
	exit 101
fi

if [ $dfsDF -gt 0 ]; then
	printf "dfs_out does not match the expected file. Your program is not printing a depth-first search output correctly for 10,000 values."
	exit 102
fi

if [ $bfsDF -gt 0 ]; then
	printf "bfs_out does not match the expected file. Your program is not printing a breadth-first search output correctly for 10,000 values."
	exit 103
fi
