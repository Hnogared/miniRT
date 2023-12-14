#!/bin/bash
# Small bash script to run the norminette on all the necessary folders and file
# of the miniRT project.

errors=0

ansi_nc="\e[0m"
ansi_error_color="\e[31m"
ansi_success_color="\e[32m"

srcs_dir="srcs"
libs_srcs_dir="${srcs_dir}/libraries"
libft_srcs_dir="${libs_srcs_dir}/extended_libft"

paths="$libft_srcs_dir"$'\n'
paths+=`ls "$srcs_dir" | grep -v "${libs_srcs_dir##*/}" | sed -e 's/^/'"$srcs_dir"'\//'`

res_paths=""

while IFS= read -r singular_path; do
	status_code=0
	res_norm=$(norminette "$singular_path")
	status_code=$?
	if [ $status_code -eq 0 ]; then
		echo -e "[${ansi_success_color}OK$ansi_nc] $singular_path"
		res_paths+="[${ansi_success_color}OK$ansi_nc] $singular_path"$'\n'
	else
		echo -e "${ansi_error_color}[KO] $singular_path$ansi_nc"
		echo -e "$res_norm"
		res_paths+="[${ansi_error_color}KO$ansi_nc] $singular_path"$'\n'
	fi
	errors=$(( errors + status_code ))
done <<< "$paths"

echo -e "\nPaths tested :\n$res_paths"
echo -n "Status code : "
if [ $errors -eq 0 ]; then
	echo -e "$ansi_success_color$errors$ansi_nc"
else
	echo -e "$ansi_error_color$errors$ansi_nc"
fi

exit $errors
