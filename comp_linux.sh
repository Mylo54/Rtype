#!/bin/bash

conan profile update settings.compiler.libcxx=libstdc++11 default
git submodule update --init --recursive
git submodule update --recursive --remote
mkdir -p build
cd build
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
cmake .. -G "Unix Makefiles"
cmake --build .