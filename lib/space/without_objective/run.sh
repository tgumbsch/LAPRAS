#!/bin/bash
# Basic while loop

g++ -std=c++14 _main.cpp -o main
rm -r ./results
mkdir results

#valgrind ./main 4 0 > results/BU4.txt 2>&1
valgrind ./main 6 0 > results/BU6.txt 2>&1
valgrind ./main 8 0 > results/BU8.txt 2>&1
valgrind ./main 10 0 > results/BU10.txt 2>&1
valgrind ./main 12 0 > results/BU12.txt 2>&1
valgrind ./main 14 0 > results/BU14.txt 2>&1
valgrind ./main 16 0 > results/BU16.txt 2>&1
valgrind ./main 18 0 > results/BU18.txt 2>&1
valgrind ./main 20 0 > results/BU20.txt 2>&1
#valgrind ./main 22 0 > results/BU22.txt 2>&1
#valgrind ./main 24 0 > results/BU24.txt 2>&1
#valgrind ./main 26 0 > results/BU22.txt 2>&1
#valgrind ./main 28 0 > results/BU24.txt 2>&1


#valgrind ./main 4 1 > results/LP4.txt 2>&1
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
valgrind ./main 28 1 > results/LP28.txt 2>&1


#valgrind ./main 4 2 > results/PW4.txt 2>&1
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
valgrind ./main 28 2 > results/PW28.txt 2>&1

#valgrind ./main 4 3 > results/SPW4.txt 2>&1
valgrind ./main 6 3 > results/SPW6.txt 2>&1
valgrind ./main 8 3 > results/SPW8.txt 2>&1
valgrind ./main 10 3 > results/SPW10.txt 2>&1
valgrind ./main 12 3 > results/SPW12.txt 2>&1
valgrind ./main 14 3 > results/SPW14.txt 2>&1
valgrind ./main 16 3 > results/SPW16.txt 2>&1
valgrind ./main 18 3 > results/SPW18.txt 2>&1
valgrind ./main 20 3 > results/SPW20.txt 2>&1
valgrind ./main 22 3 > results/SPW22.txt 2>&1
valgrind ./main 24 3 > results/SPW24.txt 2>&1
valgrind ./main 26 3 > results/SPW26.txt 2>&1
valgrind ./main 28 3 > results/SPW28.txt 2>&1

rm BU.txt
rm LP.txt
rm SPW.txt
rm PW.txt

#awk '/usage:/ {print $9}' results/BU4.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU6.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU8.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU10.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU12.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU14.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU16.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU18.txt >> BU.txt
awk '/usage:/ {print $9}' results/BU20.txt >> BU.txt
#awk '/usage:/ {print $9}' results/BU22.txt >> BU.txt
#awk '/usage:/ {print $9}' results/LP4.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP6.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP8.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP10.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP12.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP14.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP16.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP18.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP20.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP22.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP24.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP26.txt >> LP.txt
awk '/usage:/ {print $9}' results/LP28.txt >> LP.txt
#awk '/usage:/ {print $9}' results/PW4.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW6.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW8.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW10.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW12.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW14.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW16.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW18.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW20.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW22.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW24.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW26.txt >> PW.txt
awk '/usage:/ {print $9}' results/PW28.txt >> PW.txt
#awk '/usage:/ {print $9}' results/SPW4.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW6.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW8.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW10.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW12.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW14.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW16.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW18.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW20.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW22.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW24.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW26.txt >> SPW.txt
awk '/usage:/ {print $9}' results/SPW28.txt >> SPW.txt


python PowerSet.py
