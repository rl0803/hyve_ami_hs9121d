#! /bin/bash


var=$(openssl dgst -$3 -binary $1 | xxd -p | tr -d '\n')
copy=${var}
len=${#copy}
for((i=$len-2;i>=0;i-=2));do rev="$rev${copy:$i:2}";done
printf $rev | xxd -r -p | openssl rsautl -sign -inkey $4 -out $2

if [ $? -ne 0 ]; then
	rm -rf $2
fi 

