#!/bin/sh

cmake --build ./build --target clean
cmake --build ./build --target all
./build/src/lb