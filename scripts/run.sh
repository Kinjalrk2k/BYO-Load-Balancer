#!/bin/sh

cmake --build ./build --target clean
cmake --build ./build --target all
CONFIG_FILE=byolb.config ./build/src/lb