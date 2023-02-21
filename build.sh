#!/bin/sh

./clean.sh

cmake -B ./build/ -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release
cmake --build ./build/ --target package
mv ./build/*.rpm $PWD/
cp assets/ $PWD/build/Release/assets -r