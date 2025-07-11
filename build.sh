#!/usr/bin/zsh
cd build || exit 
cmake .. && make && 
if [ "$DEBUG" = "1" ]; then gdb ./Program 
else ./Program 
fi 
cd .. 