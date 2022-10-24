#!/bin/bash

mkdir -p build && cd build && conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True && cmake .. -G "Unix Makefiles"  && cmake --build .
