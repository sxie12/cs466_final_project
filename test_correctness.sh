#!/bin/sh

# declare -a dim=("2x2" "2x3" "3x2" "3x3" "3x4" "4x3" "4x4" "4x5" "5x4")
declare -a dim=("4x4")

g++ -Wall -std=c++11 -O2 skeleton_solver.cpp

for i in "${dim[@]}"
do
    d=${i:0:3}
    n=${i:0:1}
    m=${i:2:1}
    echo "Starting skeleton solver on $d"
    python generate_run_all.py $n $m > output_skeleton.txt
    echo "Finished skeleton solver"
done

g++ -Wall -std=c++11 -O2 brute_force.cpp

for i in "${dim[@]}"
do
    d=${i:0:3}
    n=${i:0:1}
    m=${i:2:1}
    echo "Starting brute force on $d"
    python generate_run_all.py $n $m > output_brute_force.txt
    echo "Finished brute force"
done
