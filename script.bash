#!/bin/bash
echo "RESULTATS: $1" > $2
echo "TEST PERF : $1"
for i in $(seq 1 1 16)
do
	for j in $(seq 1 1 5)
	do
	  echo "$j"
		(/usr/bin/time $1 $i $i) 2>&1 | awk '{print $3}' | grep 'elapsed' | cut --complement -c8-14 | tr -d '\n' >> $2
		echo ','| tr -d '\n' >>$2
	done
	echo '' >> $2
done