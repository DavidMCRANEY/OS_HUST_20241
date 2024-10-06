#!/bin/bash
# check path/directory is Null ?
if [ -z "$1" ]
then
    echo "Enter your directory"
    exit 1
fi
# check argument is directory?
if [ ! -d "$1" ] 
then
    echo "Invalid directory"
    exit 1
fi
# find empty files in directory and all sub directories
empty_files=($(find "$1" -type f -size 0))

# check directory have empty file or not?
if [ -z "$empty_files" ];then
    echo "No empty files in directory $1."
    exit 0
fi
# count the number of empty files
file_count=${#empty_files[@]}
# file_counts=$(echo "$empty_files" | wc -l). another syntax
echo "Find $file_count files have a size of 0 in directory $1 and subdirectories"
# g++ -o menu order.cpp
# ./order.exe ${empty_files[*]}


# print_menu() {
#     local idx=1
#     for file in "${empty_files[@]}"; do
#         echo "$idx. $file"
#         ((idx++))
#     done
# }
while true;do
    g++ -o menu order.cpp
    ./order.exe ${empty_files[*]}

    read -p "Enter file number you want to delete (or q to exit program):" choice
        if [[ "$choice" == "q" ]]; then
            echo "Exit."
            break
        elif [[ "$choice" =~ ^[0-9]+$ ]] && [ "$choice" -ge 1 ] && [ "$choice" -le "$file_count" ]; then
            index=$((choice-1))
            file_to_delete="${empty_files[$index]}"

            read -p "Are you sure delete $file_to_delete? (y/n): " confirm
            if [[ "$confirm" == "y" ]]; then
                rm "$file_to_delete"
                # remove file from array
                unset 'empty_files[$index]'
                # update
                empty_files=("${empty_files[@]}")
                file_count=${#empty_files[@]}

                if [ "$file_count" -eq 0 ]; then
                    echo "Noting file to delele."
                    break
                fi
            else
                echo "decline delete"
                break
            fi
        else
            echo "Please enter valid number or q to exit"
        fi      
done