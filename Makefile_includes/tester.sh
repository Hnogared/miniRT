# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnogared <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 17:44:57 by hnogared          #+#    #+#              #
#    Updated: 2024/01/07 17:45:03 by hnogared         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

if [ "$1" == "1" ]; then
	VALGRIND="valgrind --leak-check=full --show-leak-kinds=all"
fi

ERROR_DIR="scenes/error"

echo -e "\e[31m_PARSING_TESTER_\e[0m\n"

echo -e "\n\e[32m_FILE_NAME_\e[0m\n"
make -s

file_syntax=("test1.rt"
	"test.rt.rt"
	"test.rt.blabla"
	".rt.test.rt"
	"wqer.rt.qwer")

for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	./miniRT "$file_name"
	echo -e "Error code : $?\n"
done

echo -e "\e[32m_ERROR_MAP_COMMA_EVERYWHERE\e[0m\n"
make -s

file_syntax=("err_comma_everywhere_1.rt"
	"err_comma_everywhere_2.rt"
	"err_comma_everywhere_3.rt"
	"err_comma_everywhere_4.rt")

for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	$VALGRIND ./miniRT "${ERROR_DIR}/${file_name}"
	echo -e "Error code : $?\n"
done

echo -e "\e[32m_ERROR_MAP\e[0m\n"
make -s

file_syntax=("err_double_A.rt"
	"err_duplicate_C.rt"
	"err_empty_map.rt"
	"err_first_el.rt"
	"err_number.rt"
	"err_too_many_args_objects.rt"
	"err_color_range.rt"
	"err_vector_range.rt"
	"err_brightness_range.rt")

for file_name in "${file_syntax[@]}"; do
	echo -n "$file_name : "
	$VALGRIND ./miniRT "${ERROR_DIR}/${file_name}"
	echo -e "Error code : $?\n"
done
