#!/usr/bin/bash


# TEMPORARY, DON'T JUDGE

g++ -o test -DDebug=0 positions.cpp `ls ../../../src/core/*.cpp | grep -v main` -I../../../src/core
