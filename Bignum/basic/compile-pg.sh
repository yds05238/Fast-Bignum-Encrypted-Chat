#!/bin/sh
echo "Compiling program with profiler"
g++ -O3 -Wall -Wpedantic -std=c++17 main.cpp bignum.cpp -o bignum -pg
