#!/bin/bash

git submodule update --init --recursive
mkdir -p build
cd build && conan install .. --build=missing  && cmake .. -G "Visual Studio 17"  -A x64 && cmake --build . --config RELEASE
