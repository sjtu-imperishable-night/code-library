#!/bin/bash
for ((;1;))
do
./make_data
./problem1
./problem2
diff 1.out 2.out
if [ $? ¨Cne "0" ]; then
echo "fail"
exit
else
echo "pass"
fi
done