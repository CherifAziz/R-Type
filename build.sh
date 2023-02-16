#!/bin/sh

# if [ -d "$PWD/build" ]; then
#   rm -rf $PWD/build
# fi

# if [ -e "$PWD/rtype" ]; then
#   rm -rf $PWD/rtype
# fi

if [ -e "$PWD/rtype-1.0-Linux.zip" ]; then
  rm -rf $PWD/rtype-1.0-Linux.zip
fi

cmake -B ./build/ -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ./build/ --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP
cd ..
mv build/*.zip $PWD