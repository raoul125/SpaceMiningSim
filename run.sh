#!/bin/bash

# Determine the operating system
if [[ "$OSTYPE" == "linux-gnu" ]]; then
  echo "Running on Linux"
  ./bin/LunarMiningSim
elif [[ "$OSTYPE" == "darwin" ]]; then
  echo "Running on macOS"
  ./bin/LunarMiningSim
elif [[ "$OSTYPE" == "cygwin" || "$OSTYPE" == "msys" ]]; then
  echo "Running on Windows"
  ./bin/LunarMiningSim.exe
else
  echo "Unsupported platform"
  exit 1
fi
