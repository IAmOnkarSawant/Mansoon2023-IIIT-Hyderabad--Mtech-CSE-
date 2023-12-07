#! /bin/bash

path=$1
absolutepath=""

echo $absolutepath
cd
cd $path

ls -l | while read LINE
do
	ans=0
	permissions=${LINE:0:10}
	if [ ${permissions:1:1} != 'r' ] && [ ${permissions:2:1} != 'w' ] && [ ${permissions:3:1} != 'x' ] 
	then
		ans=1
	else if [ ${permissions:4:1} == 'r' ] && [ ${permissions:4:1} == 'x' ] 
	then
		ans=1	
	else
		echo ""	
	fi
	
	if (( ans == 0 ))
	then
		echo $LINE
	fi
done

