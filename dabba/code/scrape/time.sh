#! /bin/bash
while true
do
	date | sponge ../../data/date.dat
	: '
	STR=$(date)
	echo $STR >> stuff.dat
	echo $STR
	'	
	sleep 0.1s
done
