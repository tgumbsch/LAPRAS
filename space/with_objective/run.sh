#!/bin/bash
# Basic while loop


g++ -std=c++14 _main.cpp -o main

valgrind ./main 6 0 > results/BU6.txt 2>&1
valgrind ./main 8 0 > results/BU8.txt 2>&1
valgrind ./main 10 0 > results/BU10.txt 2>&1
valgrind ./main 12 0 > results/BU12.txt 2>&1
valgrind ./main 14 0 > results/BU14.txt 2>&1
valgrind ./main 16 0 > results/BU16.txt 2>&1
valgrind ./main 18 0 > results/BU18.txt 2>&1
valgrind ./main 20 0 > results/BU20.txt 2>&1
valgrind ./main 22 0 > results/BU22.txt 2>&1
valgrind ./main 24 0 > results/BU24.txt 2>&1
valgrind ./main 26 0 > results/BU26.txt 2>&1


valgrind ./main 6 1 > results/LP6.txt 2>&1
valgrind ./main 8 1 > results/LP8.txt 2>&1
valgrind ./main 10 1 > results/LP10.txt 2>&1
valgrind ./main 12 1 > results/LP12.txt 2>&1
valgrind ./main 14 1 > results/LP14.txt 2>&1
valgrind ./main 16 1 > results/LP16.txt 2>&1
valgrind ./main 18 1 > results/LP18.txt 2>&1
valgrind ./main 20 1 > results/LP20.txt 2>&1
valgrind ./main 22 1 > results/LP22.txt 2>&1
valgrind ./main 24 1 > results/LP24.txt 2>&1
valgrind ./main 26 1 > results/LP26.txt 2>&1


valgrind ./main 6 2 > results/PW6.txt 2>&1
valgrind ./main 8 2 > results/PW8.txt 2>&1
valgrind ./main 10 2 > results/PW10.txt 2>&1
valgrind ./main 12 2 > results/PW12.txt 2>&1
valgrind ./main 14 2 > results/PW14.txt 2>&1
valgrind ./main 16 2 > results/PW16.txt 2>&1
valgrind ./main 18 2 > results/PW18.txt 2>&1
valgrind ./main 20 2 > results/PW20.txt 2>&1
valgrind ./main 22 2 > results/PW22.txt 2>&1
valgrind ./main 24 2 > results/PW24.txt 2>&1
valgrind ./main 26 2 > results/PW26.txt 2>&1



awk '/usage:/ {print $5}' results/BU6.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU8.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU10.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU12.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU14.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU16.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU18.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU20.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU22.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU24.txt >> BU.txt
awk '/usage:/ {print $5}' results/BU26.txt >> BU.txt
awk '/usage:/ {print $5}' results/LP6.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP8.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP10.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP12.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP14.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP16.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP18.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP20.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP22.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP24.txt >> LP.txt
awk '/usage:/ {print $5}' results/LP26.txt >> LP.txt
awk '/usage:/ {print $5}' results/PW6.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW8.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW10.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW12.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW14.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW16.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW18.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW20.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW22.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW24.txt >> PW.txt
awk '/usage:/ {print $5}' results/PW26.txt >> PW.txt



python PowerSet.py
