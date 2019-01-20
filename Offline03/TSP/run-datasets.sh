#!/usr/bin/env bash
#best_best_NNH, best_best_SH, best_first_NNH, best_first_SH



IFS=

printRatio()
{
	output=`c++ ./Dataset.cpp -o a.out && ./a.out $1 1`
	for i in `cat out.txt` ; do
		echo $i
	done
}

printRatio 'pr76.tsp'
printRatio 'berlin52.tsp'
printRatio 'st70.tsp'
