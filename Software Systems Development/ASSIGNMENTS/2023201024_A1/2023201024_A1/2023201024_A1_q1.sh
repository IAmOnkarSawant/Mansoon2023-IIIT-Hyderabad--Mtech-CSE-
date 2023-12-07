#!/bin/bash

read -r jaggu_x jaggu_y
read -r police_x police_y
read -r H

i=1
while (( i <= H ))
do
    read -r curr_x curr_y
    
    change_x=$(bc <<< "$jaggu_x - $curr_x")
    change_y=$(bc <<< "$jaggu_y - $curr_y")
    distance=$(bc <<< "($change_x * $change_x) + ($change_y * $change_y)")
    distance=$(bc -l <<< "scale=2; sqrt($distance)")
    direction=""
     if (( $(bc <<< "$change_y > 0") )) 
    then
        if (( $(bc <<< "$change_x > 0") )) 
        then
            direction="NE"
        elif (( $(bc <<< "$change_x < 0") ))
        then
            direction="NW"
        else
            direction="N"
        fi
    elif (( $(bc <<< "$change_y < 0") ))
    then
        if (( $(bc <<< "$change_x > 0") )) 
        then
            direction="SE"
        elif (( $(bc <<< "$change_x < 0") ))
        then
            direction="SW"
        else
            direction="S"
        fi
    else
        if (( $(bc <<< "$change_x > 0") )) 
        then
            direction="E"
        else
            direction="W"
        fi
    fi

    if (( $(bc <<< "$distance < 2") ))
    then
        echo "Location reached"
        break
    elif (( i == H && $(bc <<< "$distance >= 2") ))
    then
        echo "Time over"
        break
    else
        echo "$distance $direction"
    fi

    i=$(( i+1 ))
done
