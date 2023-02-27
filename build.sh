#!/bin/sh

sudo ./clean.sh

cmake -B ./build/ -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release
cmake --build ./build/ --target package
cp $PWD/build/rtype-1.0-Linux.* $PWD/
cp assets/ $PWD/build/Release/assets -r