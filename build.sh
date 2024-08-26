#!/bin/bash

# remove the bin folder
rm -rf bin

# clean the build folder
rm -rf build/*

# Clean previous build
echo "Cleaning Previous build"
./clean.sh

cd build 

cmake .. 

cmake --build .

cd ..

mkdir bin

cp build/Debug/* bin/