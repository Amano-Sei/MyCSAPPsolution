#########################################################################
# File Name: showallsize.sh
# Author: Amano Sei
# mail: amano_sei@outlook.com
# Created Time: 2020年08月09日 星期日 14时17分59秒
#########################################################################
#!/bin/bash

for file in `ls`
do
    if [ "${file##*.}" = "rep" ]
    then
        echo $file' maxsize:'
        cat $file | head -n 1
    fi
done

