#!/bin/bash

echo -e "Hello World\n"

file_syntax=("test1.rt" "test.rt.rt" "test.rt.blabla" ".rt.test.rt" "wqer.rt.qwer")

make

echo "${#file_syntax[@]}"

for file_name in "${file_syntax[@]}"; do
	echo "$file_name :"
	./miniRT $file_name
	echo
done

