#!/bin/bash

git submodule update --init --recursive
rm -rf build && mkdir build && cd build
cmake ..
make -j$(nproc)
cd ..
