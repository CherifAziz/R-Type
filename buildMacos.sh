#!/bin/sh

./clean.sh

cmake -B ./build/ -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release
cmake --build ./build/ --target package
mv ./build/*.rpm $PWD/