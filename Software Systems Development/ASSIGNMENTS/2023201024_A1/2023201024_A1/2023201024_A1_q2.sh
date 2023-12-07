#!/bin/bash

read -r n
read -a prices
max_profit=0
min_till_now=${prices[0]}

for (( i=1; i<n; i++ ))
do 
    profit=$(( ${prices[$i]}-min_till_now ))
    if (( profit > max_profit ))
    then 
        max_profit=$profit
    fi 

    if (( min_till_now > ${prices[$i]}))
    then 
        min_till_now=${prices[$i]}
    fi
done

echo "$max_profit "