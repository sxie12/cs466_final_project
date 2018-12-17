#!/bin/sh

# declare -a dim=("2x2" "2x3" "3x2" "3x3" "3x4" "4x3" "4x4" "4x5" "5x4")
declare -a dim=("6x6" "7x7")
declare iter=5


for i in "${dim[@]}"
do
    d=${i:0:3}
    n=${i:0:1}
    m=${i:2:1}
    for ((j=1;j<=iter;j++))
    do
        echo "Generating random $d binary matrix"
        g++ -Wall -std=c++11 generate_random.cpp
        ./a.out $m $n > input_run_$i\_$j.txt
        echo "Starting skeleton solver on $d"
        g++ -Wall -std=c++11 -O2 skeleton_solver.cpp
        ./a.out -time < input_run_$i\_$j.txt > output_run_$i\_$j\_skeleton.txt
        echo "Finished skeleton solver"
        echo "Starting brute force on $d"
        g++ -Wall -std=c++11 -O2 brute_force.cpp
        ./a.out -time < input_run_$i\_$j.txt > output_run_$i\_$j\_brute_force.txt
        echo "Finished brute force"
        echo "Starting SPhyR on $d"
        ../../SPhyR/build/kDP -k 1 < input_run_$i\_$j.txt &> output_run_$i\_$j\_sphyr.txt
        echo "Finished SPhyR on $d"
    done
done


