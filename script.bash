#!/bin/bash
echo "RESULTATS: $1" > $2
for i in $(seq 1 1 20)
do
	for i in $(seq 1 1 10)
	do
		(/usr/bin/time $1 $i $i) 2>&1 | awk '{print $3}' | grep 'elapsed' | cut --complement -c8-14 | tr -d '\n' >> $2
		echo ','| tr -d '\n' >>$2
	done
	echo '' >> results.csv
done