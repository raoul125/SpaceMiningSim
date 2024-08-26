#!/bin/bash

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