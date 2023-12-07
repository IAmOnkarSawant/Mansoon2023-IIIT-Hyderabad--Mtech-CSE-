#! /bin/bash

read n
read -a a
	
for (( i=0; i<n; i++ ))
do
	curr="${a[$i]}"
	if (( a[i] == 1 ))
	then
		echo "*"
	else
		if (( curr%2 == 0 ))
		then
			continue
		else
			
			spaces=$(( a[i] / 2 ))
			spaces=$(( spaces - 1 ))
			spacer=1
			for (( j=1; j<=a[i]; j+=2 ))
			do
				for (( k=0; k<=spaces; k++ ))
				do
					echo -n "  "
				done
				spaces=$(( spaces - 1 ))
				for (( k=0; k<j; k++ ))
				do
					echo -n "* "
				done
				echo ""
			done
			for (( m=(a[i]-2); m>=0; m-=2 ))
			do
				#echo $spacer
				for (( l=0; l<spacer; l++ ))
				do
					echo -n "  "
				done
				spacer=$(( spacer + 1 ))
				for (( l=0; l<m; l++ ))
				do
					echo -n "* "
				done
				echo ""
			done
		fi
	fi
done


