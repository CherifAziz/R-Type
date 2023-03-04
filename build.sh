#!/bin/sh

cmake -B ./build/ -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release
cmake --build ./build/ --target package
if [ -e "$PWD/build/*.rpm" ]; then
  mv ./build/*.rpm $PWD/
elif [ -e "$PWD/build/*.deb" ]; then
  mv ./build/*.deb $PWD/
fi
cp assets/ $PWD/build/Release/assets -r