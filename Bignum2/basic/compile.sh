#!/bin/sh
echo "Compiling basic bignum program"
g++ -O3 -Wall -Wpedantic -std=c++17 main.cpp bignum.cpp -o bignum
