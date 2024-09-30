#!/bin/sh
svm1 $1 > tmp.s
if [[ $? == 0 ]]; then
	cc tmp.s stack.o -o $2
fi
