#! /bin/bash
# Note: To use process id to trace the process, the user will have to manually exit the process from GUI, 
# in order to get results to stdout. 

firefox &
sleep 5
sudo strace -c firefox 2>&1 | grep syscall
sudo strace -c firefox 2>&1 | grep openat
sudo strace -c firefox 2>&1 | grep close
killall firefox
# The commands below require the user to close process manually to get the result.
# sudo strace -c -p $(pidof -s firefox) 2>&1 | grep openat
# sudo strace -c -p $(pidof -s firefox) 2>&1 | grep close

java &
sleep 5
sudo strace -c java 2>&1 | grep syscall
sudo strace -c java 2>&1 | grep openat
sudo strace -c java 2>&1 | grep close
killall java