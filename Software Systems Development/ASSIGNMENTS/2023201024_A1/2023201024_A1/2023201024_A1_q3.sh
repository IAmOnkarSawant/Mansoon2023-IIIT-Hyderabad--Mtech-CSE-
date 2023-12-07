#!/bin/bash

input="q3_test_file.txt"
while IFS= read -r line
do
    ans=()
    read -ra a <<< "$line"

    # for (( j=0; j < ${#a[@]}; j++ ))
    # do
    #     echo -n "${a[$j]} "
    # done
    # echo

    for (( i=0; i < ${#a[@]}; i++ ))
    do
        if [[ ${a[i]} == "@" || ${a[i]} == "$" || ${a[i]} == "#" || ${a[i]} == "*" ]]
        then 
            ans[i]="${a[$i]}" 
        fi
    done

    front=0
    for (( back = ${#a[@]}-1 ; back >=0  ;  ))
    do
        if [[ ${ans[front]} == "@" || ${ans[front]} == "$" || ${ans[front]} == "#" || ${ans[front]} == "*" ]]
        then 
            front=$(( front + 1 ))
        elif [[ ${a[back]} == "@" || ${a[back]} == "$" || ${a[back]} == "#" || ${a[back]} == "*" ]]
        then
            back=$(( back - 1 ))
        else
            ans[front]=${a[$back]}
            front=$(( front + 1 ))
            back=$(( back - 1 ))
        fi
    done
    
    for (( i=0; i < ${#ans[@]}; i++ ))
    do
        echo -n "${ans[$i]} "
    done
    echo
    # echo "----------------------------------------------"
done < "$input"