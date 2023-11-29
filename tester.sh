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

echo -e "\e[32m_ERROR_MAP_COMMA_EVERYWHERE\e[0m\n"
make -s
file_syntax=("err_comma_everywhere_1.rt" "err_comma_everywhere_2.rt" "err_comma_everywhere_3.rt" "err_comma_everywhere_4.rt")
for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	./miniRT "scenes/${file_name}"
	echo
done

echo -e "\e[32m_ERROR_MAP\e[0m\n"
make -s
file_syntax=("err_double_A.rt" "err_duplicate_C.rt" "err_empty_line.rt" "err_empty_map.rt" "err_first_el.rt" "err_number.rt" "err_too_many_args_objects.rt" "err_color_range.rt")
for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	./miniRT "scenes/${file_name}"
	echo
done
