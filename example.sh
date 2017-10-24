#!/bin/bash
# Basic while loop

g++ -std=c++14 -c -fPIC ./lib/_main.cpp -o ./lib/LAPRAS.o
g++ -shared -Wl,-install_name,MC.so -o ./lib/LAPRAS.so ./lib/LAPRAS.o
python ./lib/PowerSet.py
