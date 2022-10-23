#!/bin/bash

# Install requirements
pip install -r scripts/requirements.txt

# Create build directory
mkdir -p build
cd ./build

# Configure CMake build
# cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake ..

# Build with CMake
cmake --build . -- -j4

# Create links to executables
ln -sf ./build/bin/encoder ../encoder
ln -sf ./build/bin/decoder ../decoder
