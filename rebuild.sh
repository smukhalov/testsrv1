#!/usr/bin/env bash

rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake final
cmake .
make