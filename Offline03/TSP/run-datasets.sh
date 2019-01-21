#!/usr/bin/env bash
#best_best_NNH, best_best_SH, best_first_NNH, best_first_SH

#'pr76.tsp' 'berlin52.tsp' 'st70.tsp'
COST[0]=108159
COST[1]=7542
COST[2]=675
FILENAME[0]='pr76.tsp'
FILENAME[1]='berlin52.tsp'
FILENAME[2]='st70.tsp'

printRatio()
{
	filename=${FILENAME[$1]}
#	echo -n "$filename "
	printf "%15s - %10.2f - %5d - " "$filename" ${COST[$1]} "100"
	IFS=
	output=`c++ ./Dataset.cpp -o a.out && ./a.out $filename 1`
	IFS=" "
	for i in `cat out.txt` ; do
		ratio=`echo "scale=2; 100*$i/${COST[$1]}" | bc`
		printf "%10.2f - %5.2f - " "$i" "$ratio"
	done
	echo ""
}

#printf "%15s - %10s - %5s - %10s - %5s - %10s - %5s \n" "filename" "cost" "Ratio" "Best NNH" "Best SH" "First NNH" "First SH"
printf "%15s - %10s - %5s - %19s - %19s - %19s - %19s \n" "filename" "cost" "Ratio" "Best NNH" "Best SH" "First NNH" "First SH"

printRatio '0'
printRatio '1'
printRatio '2'
