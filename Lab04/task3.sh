#! /bin/bash
# Note: To use process id to trace the process, the user will have to manually exit the process from GUI, 
# in order to get results to stdout. 

firefox &
sleep 1m
sudo strace -c -p $(pidof -s firefox) &> firefox.txt
val=$(cat firefox.txt)


kcalc &
sleep 1m
sudo strace -c -p $(pidof -s kcalc) &> kcalc.txt
val=$(cat kcalc.txt)

clear 

echo Firefox
echo --------------
grep errors firefox.txt
grep openat firefox.txt
grep close firefox.txt

echo kcalc
echo --------------
grep errors kcalc.txt
grep openat kcalc.txt
grep close kcalc.txt