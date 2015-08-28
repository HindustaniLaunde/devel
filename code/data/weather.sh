#!/bin/bash

while true
do
	wget -O weather.dat "http://api.openweathermap.org/data/2.5/weather?q=Kanpur" --quiet
	sleep 1m
done
