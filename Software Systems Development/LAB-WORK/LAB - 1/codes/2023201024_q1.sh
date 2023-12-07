#! /bin/bash

echo $1
lines=`cat $1 | wc -l`
onev=1
twov=2
lines=`expr $lines + $onev`
evenodd=`expr $lines % $twov`
if [ $evenodd == $onev ]
then
	lines=`expr $lines / $twov + $onev`
else
	lines=`expr $lines / $twov`
fi

FILE=`cat $1 | sort`
i=0
while read line; do
  i=$(( i + 1 ))
  case $i in $lines) echo "$line"; break;; esac
done <`cat $1 | sort`


  
