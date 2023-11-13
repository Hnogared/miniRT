#!/bin/bash

echo -e "\e[31m_PARSING_TESTER_\e[0m\n"


echo -e "\n\e[32m_FILE_NAME_\e[0m\n"
make -s
file_syntax=("test1.rt" "test.rt.rt" "test.rt.blabla" ".rt.test.rt" "wqer.rt.qwer")
for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	./miniRT $file_name
	echo
done

echo -e "\e[32m_ERROR_MAP\e[0m\n"
make -s
echo -en "\n"
file_syntax=("err_double_A.rt" "err_duplicate_C.rt" "err_empty_map.rt" "err_first_el.rt" "err_number.rt" "err_color_rage")
for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	./miniRT "scenes/${file_name}"
	echo
done
