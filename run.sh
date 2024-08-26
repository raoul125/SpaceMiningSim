#!/bin/bash

rm -rf Output/*

# Determine the operating system
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  echo "Running on Linux"
  ./bin/LunarMiningSim $1 $2 $3
elif [[ "$OSTYPE" == "darwin" ]]; then
  echo "Running on macOS"
  ./bin/LunarMiningSim $1 $2 $3
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
  echo "Running on Windows"
  ./bin/LunarMiningSim.exe $1 $2 $3
else
  echo "Unsupported platform"
  exit 1
fi

# Check if the files exist and move them if they do
if [ -f station_stat.txt ]; then
  mv station_stat.txt Output/
fi

if [ -f truck_stat.txt ]; then
  mv truck_stat.txt Output/
fi