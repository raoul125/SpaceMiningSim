#!/bin/bash

# remove the bin folder
rm -rf bin

# clean the build folder
rm -rf build/*

mkdir build

cd build 

cmake .. 

cmake --build .

cd ..

mkdir bin

if [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
    cp build/Debug/* bin/
else
    cp build/LunarMiningSim bin/
fi