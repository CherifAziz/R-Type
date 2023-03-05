#!/bin/sh

cd ecs/
cmake -B ./build/ -DCMAKE_TOOLCHAIN_FILE=$PWD/../vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release
cd ..
cmake -B ./build/ -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release --target package
cp $PWD/build/rtype-1.0-Linux.* $PWD/
cp assets/ $PWD/build/Release/assets -r