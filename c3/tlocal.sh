#########################################################################
# File Name: tlocal.sh
# Author: Amano Sei
# mail: amano_sei@outlook.com
# Created Time: 2019年09月07日 星期六 21时38分42秒
#########################################################################
#!/bin/bash

for i in `seq 1 1000000`; do
    ./tlocal >> tlocaldesu
done

