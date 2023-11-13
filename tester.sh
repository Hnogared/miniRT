#!/bin/bash

file_syntax=("test1.rt" "test.rt.rt" "test.rt.blabla" ".rt.test.rt" "wqer.rt.qwer")

echo -e "\e[41mPARSING TESTER\e[0m\n"

make

echo ""

for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name :"
	./miniRT $file_name
	echo
done

