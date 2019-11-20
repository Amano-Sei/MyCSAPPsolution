#########################################################################
# File Name: lastsh.sh
# Author: Amano Sei
# mail: amano_sei@outlook.com
# Created Time: 2019年11月19日 星期二 22时59分56秒
#########################################################################
#!/bin/bash
echo ===============================================
echo '=                   test01                    ='
echo ===============================================
make test01 > /tmp/tmp_tshoutput
make rtest01 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test02                    ='
echo ===============================================
make test02 > /tmp/tmp_tshoutput
make rtest02 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test03                    ='
echo ===============================================
make test03 > /tmp/tmp_tshoutput
make rtest03 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test04                    ='
echo ===============================================
make test04 > /tmp/tmp_tshoutput
make rtest04 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test05                    ='
echo ===============================================
make test05 > /tmp/tmp_tshoutput
make rtest05 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test06                    ='
echo ===============================================
make test06 > /tmp/tmp_tshoutput
make rtest06 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test07                    ='
echo ===============================================
make test07 > /tmp/tmp_tshoutput
make rtest07 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test08                    ='
echo ===============================================
make test08 > /tmp/tmp_tshoutput
make rtest08 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test09                    ='
echo ===============================================
make test09 > /tmp/tmp_tshoutput
make rtest09 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test10                    ='
echo ===============================================
make test10 > /tmp/tmp_tshoutput
make rtest10 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test11                    ='
echo ===============================================
make test11 > /tmp/tmp_tshoutput
make rtest11 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test12                    ='
echo ===============================================
make test12 > /tmp/tmp_tshoutput
make rtest12 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test13                    ='
echo ===============================================
make test13 > /tmp/tmp_tshoutput
make rtest13 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test14                    ='
echo ===============================================
make test14 > /tmp/tmp_tshoutput
make rtest14 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test15                    ='
echo ===============================================
make test15 > /tmp/tmp_tshoutput
make rtest15 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput
echo
echo ===============================================
echo '=                   test16                    ='
echo ===============================================
make test16 > /tmp/tmp_tshoutput
make rtest16 > /tmp/tmp_tshrefoutput
diff /tmp/tmp_tshoutput /tmp/tmp_tshrefoutput

