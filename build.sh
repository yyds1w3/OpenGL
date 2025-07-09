#!/usr/bin/zsh
cd build || exit 
cmake .. && make && ./Program 
cd .. 

