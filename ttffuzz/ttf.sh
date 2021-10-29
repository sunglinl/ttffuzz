#！/bin/bash

for I in {1..200000};do
	echo "start\n"
	echo "fuzz is  : $I"
	./ttf-fuzzer fuzz test.ttf
	sleep 1s
	./test test.ttf &
	echo "sleep start\n"
	sleep 1s
	echo "kill start\n"
	ps -efww|grep -w 'Font'|grep -v grep|cut -c 7-17|xargs kill -9
done
	echo "over\n"
	exit 0
